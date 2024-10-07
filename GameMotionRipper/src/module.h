#include <Windows.h>
#include <string>
#include <vector>
#include <memory>
#pragma once

struct NXModule
{
	DWORD   pID = 0;
	HANDLE  pHandle = 0;
	DWORD64 clientBase = 0;
	DWORD64 imageSize = 0;
};

namespace NXApp 
{
	uintptr_t                 getProcessBaseAddress(DWORD processId, HANDLE processHandle);
	std::shared_ptr<NXModule> getModuleFromWindow(const char* windowTitle);
}

