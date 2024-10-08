#include <nxripper.h>
#include <json.hpp>
#pragma once

using JSON = nlohmann::ordered_json;

// NXRipTrack - defines ripper controller target ie. Actor0, Actor1, Camera0 etc.
struct NXRipTrack
{
	std::string name;
	int16_t     index = -1; // used to link animframe keys with threads
	uint16_t    numEntities = 0;
	uintptr_t   address = 0;
	uint32_t    numKeys = 0;
};

// NXRipperPreset - defines a ripper preset and its properties for a specific game
class CNXRipperPreset
{
public:
	CNXRipperPreset();
	~CNXRipperPreset();

public:
	void setName(const char* name);
	void setProcess(const char* process_name);
	void setTickRate(int rate);
	void setRipDuration(int duration);
	void addTrack(const uintptr_t address, const uint16_t entityCount, const std::string name = "");
	void addTrack(NXRipTrack& track);
	
public:
	static std::shared_ptr<CNXRipperPreset> makeDefault();
	std::string name() const;
	std::string process() const;
	int trackCount() const;
	int tickRate() const;

public:
	bool save(const char* path) const;
	bool empty() const;
	void fromFile(const char* path);
	std::vector<NXRipTrack>& tracks();

private:
	inline JSON toJson() const;

private:
	std::string m_name;
	std::string m_processName;
	int m_tickRate;
	int m_ripDuration;
	std::vector<NXRipTrack> m_tracks;
};



