#include <nxrippreset.h>
#include <fstream>

CNXRipperPreset::CNXRipperPreset()
	:
	m_tickRate(0),
	m_ripDuration(0),
	m_numChannels(0)
{
}

CNXRipperPreset::~CNXRipperPreset()
{
}

JSON
CNXRipperPreset::toJson() const
{
	JSON j, targets;
	j["name"] = m_name;
	j["process"] = m_processName;
	j["tick_rate"] = m_tickRate;
	j["rip_duration"] = m_ripDuration;
	j["channel_count"] = m_numChannels;

	for (auto& target : m_targets)
	{
		JSON t;
		t["name"] = target.name;
		t["address"] = target.address;
		targets.push_back(t);
	}
	j["targets"] = targets;
	return j;
}

bool
CNXRipperPreset::save(const char* path) const
{
	// Create JSON object
	auto data = this->toJson();

	// Write JSON object to file
	std::ofstream file(path);
	if (!file.is_open())
		return false;

	file << data.dump(4);
	file.close();
	return true;
}

inline static JSON getJsonFromFile(const char* path)
{
	JSON inJson;
	std::ifstream file(path);
	if (!file.is_open())
		return inJson;

	file >> inJson;
	file.close();
	return inJson;
}

void
CNXRipperPreset::fromFile(const char* path)
{
	try {
		JSON json = ::getJsonFromFile(path);

		// Populate data from JSON object
		m_name        = json["name"];
		m_processName = json["process"];
		m_tickRate    = json["tick_rate"];
		m_ripDuration = json["rip_duration"];
		m_numChannels = json["channel_count"];

		JSON targets = json["targets"];
		if (targets.empty())
			return;

		for (auto& target : targets)
		{
			NXRipTarget t;
			t.name = target["name"];
			t.address = target["address"];
			m_targets.push_back(t);
		}
	}
	catch (...)
	{
		printf("\n[NXPreset] Invalid or empty preset file: %s\n", path);
	}
}


bool
CNXRipperPreset::empty() const
{
	return m_name.empty() || m_processName.empty() || m_numChannels == 0;
}

void 
CNXRipperPreset::setName(const char* name)
{
	m_name = name;
}

void 
CNXRipperPreset::setProcess(const char* process_name)
{
	m_processName = process_name;
}

void 
CNXRipperPreset::setDefaultTickRate(int rate)
{
	m_tickRate = rate;
}

void 
CNXRipperPreset::setDefaultRipDuration(int duration)
{
	m_ripDuration = duration;
}

void 
CNXRipperPreset::setDefaultChannelCount(int count)
{
	m_numChannels = count;
}

const std::vector<NXRipTarget>& 
CNXRipperPreset::getTargets() const
{
	return m_targets;
}

std::shared_ptr<CNXRipper>
CNXRipperPreset::ripper() const
{
	auto ripper = std::make_shared<CNXRipper>();
	return ripper;
}

std::string
CNXRipperPreset::name() const
{
	return m_name;
}

std::string
CNXRipperPreset::process() const
{
	return m_processName;
}
