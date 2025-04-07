
#include "texturepacks.h"
#include "t1_system/files/files.h"
#include <fstream>
#include <unordered_set>
#include <cereal/types/unordered_set.hpp>
#include <cereal/archives/json.hpp>

namespace stdfs = std::filesystem;
static const stdfs::path images("images");
static const stdfs::path config("settings/texturepacks.json");
static std::unordered_set<std::string> allPacks;
static std::unordered_set<std::string> activePacks;

void Texturepacks::saveConfig()
{
	t1::system::tryCreateFolder("settings");
	std::ofstream fout(config);
	cereal::JSONOutputArchive archive(fout);
	archive(cereal::make_nvp("active_packs", activePacks));
}

void Texturepacks::loadConfig()
{
	try
	{
		std::ifstream fin(config);
		cereal::JSONInputArchive archive(fin);
		archive(cereal::make_nvp("active_packs", activePacks));
	}
	catch (std::runtime_error&) // If active texturepacks file does not exist.
	{
		std::cout << "Texturepacks file not found. Default vanilla pack applied.\n";
		clearActivePacks();
		saveConfig();
	}
}


void Texturepacks::findPacks()
{
	if (!stdfs::exists(images))
		return;
	for (const auto& entry : stdfs::directory_iterator(images))
		if (stdfs::is_directory(entry))
			allPacks.emplace(entry.path().filename().string());
}

stdfs::path Texturepacks::findImage(const std::string& fileName)
{
	for (const std::string& pack : activePacks)
	{
		const stdfs::path path = images / pack / fileName;
		if (stdfs::exists(path))
			return path;
	}
	return images / "vanilla" / fileName;
}


void Texturepacks::pushActivePack(const std::string& packName)
{
	stdfs::path path = images / packName;
	if (stdfs::exists(path) && stdfs::is_directory(path))
		activePacks.emplace(packName);
}

void Texturepacks::removeActivePack(const std::string& packName)
{
	activePacks.erase(packName);
}

void Texturepacks::clearActivePacks()
{
	activePacks.clear();
}
