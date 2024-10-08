#include <nxriplibrary.h>
#include <common.h>

CNXRipperLib::CNXRipperLib()
	//:
{
}

CNXRipperLib::~CNXRipperLib()
{
}


bool
CNXRipperLib::empty() const
{
	return m_presets.empty();
}

void
CNXRipperLib::addPreset(const CNXRipperPreset& preset)
{
	m_presets.push_back(preset);
}

void 
CNXRipperLib::loadPresets()
{
	// Get library directory path 
	if (!hasDiskLibrary())
		return;
	
	// Find .prst files in library directory
	auto paths = common::findMatchingExtensionFiles(m_libraryPath.c_str(), ".prst");

	for (auto& path : paths)
	{
		CNXRipperPreset preset;
		preset.fromFile(path.c_str());
		
		if (!preset.empty())
		{
			this->addPreset(preset);
		}
	}
}

CNXRipperLib 
CNXRipperLib::fromDirectory(const char* path)
{
	return CNXRipperLib();
}

bool
CNXRipperLib::save()
{
	if (!hasDiskLibrary())
		return false;

	for (auto& preset : m_presets)
	{
		auto savePath = m_libraryPath + "/" + preset.name() + ".prst";
		preset.save(savePath.c_str());
	}

	return true;
}

bool
CNXRipperLib::hasDiskLibrary()
{
	m_libraryPath = (m_libraryPath.empty()) ? getLocalPath() : m_libraryPath;
	if (m_libraryPath.empty())
		return false;

	return common::create_folder(m_libraryPath);
}

void
CNXRipperLib::setLibraryPath(const char* path)
{
	m_libraryPath = path;
}

std::string
CNXRipperLib::getLocalPath()
{
	auto home = common::get_exe_path();
	return home.empty() ? home : (home + "/RipperPresets");
}

#ifdef BUILD_DEBUG_PRESETS
	
    inline static void addDummyPreset(CNXRipperLib& lib, const char* name)
	{
		CNXRipperPreset preset;
		preset.setName(name);
		preset.setProcess("dummy.exe");
		preset.setTickRate(60);
		preset.setRipDuration(1000);
		preset.setChannelCount(1);
		lib.addPreset(preset);
	}

	CNXRipperLib CNXRipperLib::fromDevPresets()
	{
		printf("\n[CNXRipperLib] Building default presets.\n");

		CNXRipperLib lib;
		lib.loadPresets();

		if (lib.empty())
		{
			::addDummyPreset(lib, "GameDummyA");
			::addDummyPreset(lib, "OtherGameDummyB");

			lib.addPreset( *CNXRipperPreset::makeDefault().get() );
		}

		lib.save();
		return lib;
	}
#endif