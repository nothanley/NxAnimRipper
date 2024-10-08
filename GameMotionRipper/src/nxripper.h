#include <memory>
#include <chrono>
#include <nxanimrip.h>
#include <mutex>
#pragma once

//Forward declarations
class CNXProcess;
class CNXRipperPreset;
struct NXRipTarget;

// Class declarations
class CNXRipper
{
public:
	CNXRipper();
	~CNXRipper();

public:
	bool run();
	bool empty() const;
	bool linkProcess(const char* process_name);

public:
	std::vector<CNXAnimFrame>& frames();
	std::shared_ptr<CNXRipperPreset>& config();
	std::shared_ptr<CNXProcess>& process();

private:
	void startRipThreads();
	void addNxFrame(const CNXAnimFrame& frame);
	void processTargetFrame(const NXRipTarget& target, int num_bones);
	void thread(const NXRipTarget& target, int num_bones, const std::chrono::milliseconds& frame_time);

private:
	std::mutex m_mutex;
	bool  m_isRunning;
	float m_timer;
	std::shared_ptr<CNXRipperPreset> m_config;
	std::shared_ptr<CNXProcess>      m_process;
	std::vector<CNXAnimFrame>        m_frames;
};

