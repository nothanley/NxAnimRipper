#include <nxripper.h>
#include <json.hpp>
#pragma once

using JSON = nlohmann::ordered_json;

// NXRipTarget - defines ripper controller target ie. Actor0, Actor1, Camera0 etc.
struct NXRipTarget
{
	std::string name;
	uintptr_t   address;
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
	void setChannelCount(int count);
	void setOffset(uintptr_t offset);
	
public:
	static std::shared_ptr<CNXRipperPreset> makeDefault();
	std::string name() const;
	std::string process() const;
	int tickRate() const;
	int channelCount() const;
	uintptr_t offset() const;

public:
	bool save(const char* path) const;
	bool empty() const;
	void fromFile(const char* path);
	const std::vector<NXRipTarget>& getTargets() const;

private:
	inline JSON toJson() const;

private:
	std::string m_name;
	std::string m_processName;
	uintptr_t m_targetOffset;
	int m_tickRate;
	int m_ripDuration;
	int m_numChannels;
	std::vector<NXRipTarget> m_targets;
};



