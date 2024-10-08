#include <nxrippreset.h>
#include <fstream>

CNXRipperPreset::CNXRipperPreset()
	:
	m_tickRate(0),
	m_ripDuration(0),
	m_numChannels(0),
	m_targetOffset(0)
{
}

CNXRipperPreset::~CNXRipperPreset()
{
}

JSON
CNXRipperPreset::toJson() const
{
	JSON j, targets;
	j["name"]          = m_name;
	j["process"]       = m_processName;
	j["target_offset"] = m_targetOffset;
	j["tick_rate"]     = m_tickRate;
	j["rip_duration"]  = m_ripDuration;
	j["channel_count"] = m_numChannels;

	for (auto& target : m_targets)
	{
		JSON t;
		t["name"]    = target.name;
		t["address"] = target.address;
		t["index"]   = target.index;
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
		m_name         = json["name"];
		m_processName  = json["process"];
		m_targetOffset = json["target_offset"];
		m_tickRate     = json["tick_rate"];
		m_ripDuration  = json["rip_duration"];
		m_numChannels  = json["channel_count"];

		JSON targets = json["targets"];
		if (targets.empty())
			return;

		for (auto& target : targets)
		{
			NXRipTarget t;
			t.name	  = target["name"];
			t.address = target["address"];
			t.index   = -1;
			m_targets.push_back(t);
		}
	}
	catch (...)
	{
		printf("\n[NXPreset] Invalid or empty preset file: %s\n", path);
	}
}

std::shared_ptr<CNXRipperPreset>
CNXRipperPreset::makeDefault()
{
	auto preset = std::make_shared<CNXRipperPreset>();
	preset->setName("Default");
	preset->setProcess("DefaultProcess");
	preset->setTickRate(60);
	preset->setRipDuration(5000);
	preset->setChannelCount(1);
	return preset;
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
CNXRipperPreset::setTickRate(int rate)
{
	m_tickRate = rate;
}

void 
CNXRipperPreset::setRipDuration(int duration)
{
	m_ripDuration = duration;
}

void 
CNXRipperPreset::setChannelCount(int count)
{
	m_numChannels = count;
}

void
CNXRipperPreset::setOffset(uintptr_t offset)
{
	m_targetOffset = offset;
}

const std::vector<NXRipTarget>& 
CNXRipperPreset::targets() const
{
	return m_targets;
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

uintptr_t
CNXRipperPreset::offset() const
{
	return m_targetOffset;
}

int
CNXRipperPreset::tickRate() const
{
	return m_tickRate;
}

int
CNXRipperPreset::channelCount() const
{
	return m_numChannels;
}
