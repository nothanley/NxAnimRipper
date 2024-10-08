#include <memory>
#include <chrono>
#include <nxanimrip.h>
#pragma once

//Forward declarations
class CNXProcess;
class CNXRipperPreset;

// Class declarations
class CNXRipper
{
public:
	CNXRipper();
	~CNXRipper();

public:
	void run();
	bool empty() const;
	bool linkProcess(const char* process_name);

public:
	std::vector<CNXAnimFrame>& frames();
	std::shared_ptr<CNXRipperPreset>& config();

private:
	void initRipThread();
	void ripNxProcess();

private:
	float m_timer;
	std::shared_ptr<CNXRipperPreset> m_config;
	std::unique_ptr<CNXProcess>      m_process;
	std::vector<CNXAnimFrame>        m_frames;
};

