#include <nxripper.h>
#include <nxprocess.h>
#include <nxrippreset.h>
#include <thread>

#define time_cast std::chrono::duration_cast<std::chrono::milliseconds>
using namespace std::chrono;

CNXRipper::CNXRipper()
	:
	m_timer(10000), // Default 10 second timer
	m_isRunning(false)
{
	this->m_config = CNXRipperPreset::makeDefault();
}

CNXRipper::~CNXRipper()
{
}

bool 
CNXRipper::empty() const
{
	return m_frames.empty();
}

std::vector<CNXAnimFrame>& 
CNXRipper::frames()
{
	return m_frames;
}

std::shared_ptr<CNXRipperPreset>&
CNXRipper::config()
{
	return m_config;
}

bool
CNXRipper::linkProcess(const char* process_name)
{
	m_process = std::make_shared<CNXProcess>(process_name);
	return m_process->load();
}

void
CNXRipper::addNxFrame(const CNXAnimFrame& frame)
{
	// handle race conditions with mutex
	m_mutex.lock();

	// push target keyframe and unlock mutex
	m_frames.push_back(frame);
	m_mutex.unlock();
}

void 
CNXRipper::processTargetFrame(const NXRipTarget& target, int num_bones)
{
	// Defines frame by frame logic for worker threads
	std::vector<uint8_t> buffer; 
	size_t size = num_bones * NXMATRIX_LEN;

	if (!m_process->loadMemChunk(target.address, size, buffer))
		return;

	// Process recieved data
	CNXAnimFrame frame;
	frame.load((char*)buffer.data(), buffer.size());
	frame.setTarget(target.index);

	if (!frame.empty())
		CNXRipper::addNxFrame(frame);
}

void
CNXRipper::thread(const NXRipTarget& target, int num_bones, const milliseconds& frame_time)
{
	// Runs concurrent frame processing for specified animation target
	// while the timed or untimed main thread is requesting data
	while (m_isRunning)
	{
		processTargetFrame(target, num_bones);
		std::this_thread::sleep_for(frame_time);
	}
}

void
CNXRipper::startRipThreads()
{
	if (!m_process || m_config->targets().empty() || m_config->channelCount() == 0)
		return;

	// Initializes and detaches target threads
	// for each specified animation controller
	this->m_isRunning = true;
	auto numBones     = m_config->channelCount();
	auto frameTiming  = milliseconds(100 / m_config->tickRate());

	for (auto& target : m_config->targets())
	{
		std::thread worker(&CNXRipper::thread, this, target, numBones, frameTiming);
		worker.detach();
	}
}

bool 
CNXRipper::run()
{
	auto startTime   = high_resolution_clock::now();
	auto currentTime = startTime;
	this->startRipThreads();

	if (!m_isRunning)
		return false;
	
	// Timed update loop - counts down then stops all ripper threads
	printf("[NXRipper] Ripper initialized | Timer: %f(ms)\n", m_timer);
	while (time_cast(currentTime - startTime).count() < m_timer)
	{
		printf("\n[NXRipper] Time remaining: %f(ms)\n", m_timer - time_cast(currentTime - startTime).count());
		currentTime = high_resolution_clock::now();
	}

	m_isRunning = false;
	return true;
}


