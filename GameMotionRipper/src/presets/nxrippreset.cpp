#include <nxrippreset.h>
#include <fstream>

CNXRipperPreset::CNXRipperPreset()
	:
	m_tickRate(0),
	m_ripDuration(0)
{
}

CNXRipperPreset::~CNXRipperPreset()
{
}

JSON
CNXRipperPreset::toJson() const
{
	JSON j, tracks;
	j["name"]          = m_name;
	j["process"]       = m_processName;
	j["tick_rate"]     = m_tickRate;
	j["rip_duration"]  = m_ripDuration;

	std::vector<JSON> trackObjs(m_tracks.size());
	for (int i = 0; i < trackObjs.size(); ++i)
	{
		JSON t;
		auto& track = m_tracks[i];

		t["name"]         = track.name;
		t["address"]      = track.address;
		t["entity_count"] = track.numEntities;
		t["keyframes"]    = track.numKeys;
		t["index"]        = track.index;

		trackObjs[i] = t;
	}

	j["tracks"]= trackObjs;
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
		m_tickRate     = json["tick_rate"];
		m_ripDuration  = json["rip_duration"];

		JSON tracks    = json["tracks"];
		if (tracks.empty())
			return;

		for (auto& track : tracks)
		{
			NXRipTrack t;
			t.name	      = track["name"];
			t.address     = track["address"];
			t.numEntities = track["entity_count"];
			m_tracks.push_back(t);
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
	return preset;
}

bool
CNXRipperPreset::empty() const
{
	return m_name.empty() || m_processName.empty() || m_tracks.empty();
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
CNXRipperPreset::addTrack(
	const uintptr_t address, 
	const uint16_t entityCount,
	const std::string name)
{

	NXRipTrack track;
	track.address = address;
	track.numEntities = entityCount;
	track.name = name;

	m_tracks.push_back(track);
}

void
CNXRipperPreset::addTrack(NXRipTrack& track)
{
	if (track.address = 0 || track.numEntities == 0)
		return;

	m_tracks.push_back(track);
}

int
CNXRipperPreset::trackCount() const
{
	return m_tracks.size();
}

std::vector<NXRipTrack>& 
CNXRipperPreset::tracks()
{
	return m_tracks;
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

int
CNXRipperPreset::tickRate() const
{
	return m_tickRate;
}
