#include <nxripper.h>
#include <nxprocess.h>
#include <thread>

#define time_cast std::chrono::duration_cast<std::chrono::milliseconds>
using namespace std::chrono;

CNXRipper::CNXRipper()
	: m_tickRate(60)
	, m_targetCount(0)
	, m_targetOffset(0)
	, m_timer(10000)
{
}

CNXRipper::~CNXRipper()
{
}

bool CNXRipper::empty() const
{
	return m_frames.empty();
}

std::vector<CNXAnimFrame>& CNXRipper::frames()
{
	return m_frames;
}

void CNXRipper::setTickRate(int rate)
{
	m_tickRate = rate;
}

void CNXRipper::setManualTargets(uintptr_t target_address, const int bone_count)
{
	m_targetCount  = bone_count;
	m_targetOffset = target_address;
}

void CNXRipper::setRipDuration(int duration)
{
	m_timer = duration;
}

void CNXRipper::run()
{
	if (!m_process) return;

	auto frameTime   = milliseconds(100 / m_tickRate);
	auto startTime   = high_resolution_clock::now();
	auto currentTime = startTime;
	printf("[NXRipper] Ripper initialized | Timer: %f(ms)\n", m_timer);

	while (time_cast(currentTime - startTime).count() < m_timer)
	{
		this->ripNxProcess();

		std::this_thread::sleep_for(frameTime);
		currentTime = high_resolution_clock::now();
	}
}

bool CNXRipper::linkProcess(const char* process_name)
{
	m_process = std::make_unique<CNXProcess>(process_name);
	m_process->load();

	return true;
}

void CNXRipper::ripNxProcess()
{
	// Validate linked process
	if (!m_process || m_targetCount <= 0)
		return;

	// Load target memory chunk
	size_t size = m_targetCount * NXMATRIX_LEN; // context: 0x40 is the size of a single bone matrix
	std::vector<uint8_t> buffer;
	if (!m_process->loadMemChunk(m_targetOffset, size, buffer))
		return;

	// Process recieved data
	CNXAnimFrame frame;
	frame.load((char*)buffer.data(), buffer.size());

	if (!frame.empty()) 
	{
		m_frames.push_back(frame);
	}
}


