#include <memory>
#include <chrono>
#include <nxanimrip.h>
#pragma once

//Forward declarations
class CNXProcess;

// Class declarations
class CNXRipper
{
public:
	CNXRipper();
	~CNXRipper();

public:
	bool empty() const;
	std::vector<CNXAnimFrame>& frames();
	void run();
	bool linkProcess(const char* process_name);

public:
	void setRipDuration(int duration);
	void setManualTargets(uintptr_t target_address, const int bone_count);
	void setTickRate(int rate);

private:
	void ripNxProcess();

private:
	float     m_timer;
	int       m_tickRate;
	int       m_targetCount;
	uintptr_t m_targetOffset;
	std::unique_ptr<CNXProcess> m_process;
	std::vector<CNXAnimFrame>   m_frames;
};



