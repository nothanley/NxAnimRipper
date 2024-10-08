#include <nxripfile.h>
#include <fstream>
#include <common.h>
#include <chrono>

CNXRipFile::CNXRipFile()
    :
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
    if (!m_frames)
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

void CNXRipFile::buildAnimJson(JSON& json)
{
    int i = 0;
    json["NumFrames"] = m_frames->size();

    for (auto& frame : *m_frames)
    {
        JSON f;
        f["Target"]      = frame.target();
        f["NumChannels"] = frame.channels().size();

        for (auto& channel : frame.channels())
        {
            JSON child;
            //auto translate = channel.matrix.translation();

            child["id"]                   =   channel.id;
            child["matrix"]               =   channel.matrix.to_vector();
            //child["translation"]        = { translate.x, translate.y, translate.z };
            f[std::to_string(channel.id)] =   child;
        }

        json["Frame" + std::to_string(i)] = f;
        ++i;
    }
}
