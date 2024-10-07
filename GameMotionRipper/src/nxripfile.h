#include <vector>
#include <string>
#include <nxanimrip.h>
#include <json.hpp>
#pragma once

using JSON = nlohmann::ordered_json;

class CNXRipFile
{
public:
	CNXRipFile();
	~CNXRipFile();

public:
	void setFrames(std::vector<CNXAnimFrame>* frames);
	void saveToFile(const char* directory_path);

private:
	void buildAnimJson(JSON& json);

private:
	std::string m_filePath;
	std::vector<CNXAnimFrame>* m_frames;
};