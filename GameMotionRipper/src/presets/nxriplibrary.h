#include <nxrippreset.h>
#pragma once

class CNXRipperLib 
{
public:
	CNXRipperLib();
	~CNXRipperLib();

public:
	static CNXRipperLib fromDirectory(const char* path);
	static std::string getLocalPath();

public:
	bool empty() const;
	bool save();
	void addPreset(const CNXRipperPreset& preset);
	void loadPresets();
	void setLibraryPath(const char* path);

private:
	bool hasDiskLibrary();

private:
	std::string m_libraryPath;
	std::vector<CNXRipperPreset> m_presets;

// Debug utility
#ifdef BUILD_DEBUG_PRESETS
	public:
	static CNXRipperLib fromDevPresets();
#endif
};

