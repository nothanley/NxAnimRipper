#include <memory>
#include <chrono>
#include <nxanimframe.h>
#include <mutex>
#pragma once

//Forward declarations
class CNXProcess;
class CNXRipperPreset;
struct NXRipTrack;

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
	void processTrackKeyFrame(NXRipTrack& target, int num_bones, int frame_index);
	void thread(NXRipTrack& track, const std::chrono::milliseconds frame_time);

private:
	bool  m_isRunning;
	float m_timer;
	std::mutex m_mutex;
	std::shared_ptr<CNXRipperPreset> m_config;
	std::shared_ptr<CNXProcess>      m_process;
	std::vector<CNXAnimFrame>        m_frames;
};

