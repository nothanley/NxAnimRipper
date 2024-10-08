#include <vector>
#include <string>
#include <nxanimframe.h>
#include <json.hpp>
#pragma once

using JSON = nlohmann::ordered_json;

class CNXRipper;

class CNXRipFile
{
public:
	CNXRipFile(CNXRipper* ripper);
	~CNXRipFile();

public:
	void setFrames(std::vector<CNXAnimFrame>* frames);
	void saveToFile(const char* directory_path);

private:
	void buildAnimJson(JSON& json);

private:
	std::string m_filePath;
	CNXRipper* m_ripper;
	std::vector<CNXAnimFrame>* m_frames;
};