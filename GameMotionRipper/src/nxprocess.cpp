#include <nxprocess.h>
#include <module.h>


CNXProcess::CNXProcess(const char* process_name)
	: m_processName(process_name)
{
}


CNXProcess::~CNXProcess()
{
}

void CNXProcess::findProcess()
{
	// Find the process by name
	this->m_module = NXApp::getModuleFromWindow(m_processName.c_str());
	if (!m_module)
		return;


	printf("Process ID: %d\n", m_module->pID);
}

bool CNXProcess::load()
{
	if (m_processName.empty())
		return false;

	this->findProcess();

	return m_module != nullptr;
}

bool CNXProcess::loadMemChunk(uintptr_t offset, size_t size, std::vector<uint8_t>& buffer)
{
	if (!m_module)
		return false;

	buffer.resize(size);
	//uintptr_t address = m_module->clientBase + offset;
	uintptr_t address = offset;
	auto result = ReadProcessMemory(m_module->pHandle, (LPCVOID)address, buffer.data(), size, NULL);

	return result;
}

