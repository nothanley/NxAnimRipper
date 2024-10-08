#include <nxripfile.h>
#include <nxripper.h>
#include <nxrippreset.h>
#include <fstream>
#include <common.h>
#include <chrono>
#

CNXRipFile::CNXRipFile(CNXRipper* ripper)
    :
    m_ripper(ripper),
    m_frames(nullptr)
{
}

CNXRipFile::~CNXRipFile()
{
}

void CNXRipFile::setFrames(std::vector<CNXAnimFrame>* frames)
{
    this->m_frames = frames;
}

inline static std::string getTimestamp()
{
    char buffer[20];
    std::tm timeinfo;

    auto now = std::chrono::system_clock::now();
    auto now_t = std::chrono::system_clock::to_time_t(now);
    localtime_s(&timeinfo, &now_t);
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d-%H-%M-%S", &timeinfo);
    return std::string(buffer);
}

inline static std::string getSaveFileName(const char* directory)
{
    return std::string(directory) + "/nxmotionrip.json";
}

void CNXRipFile::saveToFile(const char* directory_path)
{
    if (!m_frames || !m_ripper)
        return;

    std::string savePath = ::getSaveFileName(directory_path);
    if (savePath.empty())
        return;

    JSON json;
    printf("[CNXRipFile] Saving to: %s\n", savePath.c_str());
    buildAnimJson(json);

    std::ofstream file(savePath);
    if (!file.is_open())
        return;

    file << json.dump(4);
    printf("[CNXRipFile] File saved: %s\n", savePath.c_str());
}

inline static JSON getTrackEntityTfmJson(CNXAnimFrame& frame)
{
    JSON obj;

    for (auto& entity : frame.entities())
    {
        JSON child;
        child["matrix"] = entity.matrix.to_vector();
        obj[std::to_string(entity.id)] = child;
    }

    return obj;
}

void CNXRipFile::buildAnimJson(JSON& json)
{
    auto& config = m_ripper->config();
    json["overall frames"] = m_frames->size();
    json["overall tracks"] = config->trackCount();

    for (auto& track : config->tracks())
    {
        JSON t;
        t["num keys"] = track.numKeys;
        t["num entities"] = track.numEntities;
        json[track.name] = t;
    }

    int i = 0;
    for (auto& frame : *m_frames)
    {
        JSON f;
        f["key"]      = frame.key();
        f["track"]    = frame.track();
        f["entities"] = ::getTrackEntityTfmJson(frame);

        json["Frame" + std::to_string(i)] = f;
        ++i;
    }
}


