#include <vector>
#include <memory>
#include <string>
#include <Windows.h>
#pragma once

// Forward declarations
struct NXModule;

// Class declarations
class CNXProcess
{
public:
	CNXProcess(const char* process_name);
	~CNXProcess();

public:
	bool load();
	bool loadMemChunk(uintptr_t offset, size_t size, std::vector<uint8_t>& buffer);

private:
	void findProcess();

private:
	std::shared_ptr<NXModule> m_module;
	std::string m_processName;
};

