#include <module.h>
#include <stdio.h>

// Windows Process Helper libraries
#include <tlhelp32.h>
#include <psapi.h>  // Include psapi.h for GetModuleInformation
#pragma comment(lib, "psapi.lib")  // Link with psapi.lib


BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam)
{
    char buffer[256];
    GetWindowTextA(hwnd, buffer, 256);
    std::string title(buffer);
    std::vector<std::string>* windowTitles = reinterpret_cast<std::vector<std::string>*>(lParam);
    windowTitles->push_back(title);
    return TRUE;
}

inline std::string findWindow(const char* windowTitle)
{
	std::vector<std::string> windowTitles;
	EnumWindows(EnumWindowsProc, reinterpret_cast<LPARAM>(&windowTitles));
	for (const auto& title : windowTitles)
	{
		if (title.find(windowTitle) != std::string::npos)
			return title;
	}
	return "";
}

std::shared_ptr<NXModule>
NXApp::getModuleFromWindow(const char* windowTitle)
{
	DWORD processId = 0;
    auto window = findWindow(windowTitle);         // Find full window title 
	HWND hwnd = FindWindowA(NULL, window.c_str()); // Find window handle

	if (hwnd == NULL)
	{
		return nullptr;
	}

	GetWindowThreadProcessId(hwnd, &processId);
	auto module       = std::make_shared<NXModule>();
	module->pID        = processId;
	module->pHandle    = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processId);

	if (module->pHandle == NULL)
	{
		printf("Failed to open process handle for: %s\n", windowTitle);
		return nullptr;
	}

	module->clientBase = getProcessBaseAddress(processId, module->pHandle);
	return module;
}

uintptr_t 
NXApp::getProcessBaseAddress(DWORD processID, HANDLE hProcess)
{
    MODULEENTRY32 moduleEntry;
    moduleEntry.dwSize = sizeof(MODULEENTRY32);

    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, processID);
    if (hSnapshot == INVALID_HANDLE_VALUE)
		return 0;

	uintptr_t base =
		(Module32First(hSnapshot, &moduleEntry)) ? uintptr_t(moduleEntry.modBaseAddr) : 0;

	CloseHandle(hSnapshot);
	return base;
}

