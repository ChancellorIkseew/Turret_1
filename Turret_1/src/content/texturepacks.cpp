
#include "texturepacks.h"
#include <algorithm>
#include <vector>
#include <iostream>
#include <fstream>
#include <cpptoml.h>

namespace stdfs = std::filesystem;
static const stdfs::path images("images");
static const stdfs::path vanilla(images / "vanilla");
static std::vector<stdfs::path> allPacks;
static std::vector<stdfs::path> activePacks;

void Texturepacks::saveConfig()
{
	std::ofstream fout;
	fout.open("settings/texturepacks.toml");
	if (!fout.is_open())
		throw std::runtime_error("Unable to open file to write: settings/texturepacks.toml"); // Should not be catched. (crash the game)
	auto packs = cpptoml::make_array();
	for (const auto& path : activePacks)
		packs->push_back(path.filename().string());
	cpptoml::toml_writer writer(fout, " ");
	writer.visit(*packs, false);
	fout.close();
}

void Texturepacks::loadConfig()
{
	try
	{
		const auto config = cpptoml::parse_file("settings/texturepacks.toml");
		const auto packs = config->get_array_of<std::string>("active_packs");
		for (auto& pack : *packs)
			activePacks.emplace_back(images / pack);
	}
	catch (cpptoml::parse_exception) // If active texturepacks file does not exist.
	{
		std::cout << "Texturepacks file not found. Default vanilla pack applied.\n";
		resetActivePacks();
		saveConfig();
	}
}


void Texturepacks::findPacks()
{
	if (!stdfs::exists(images))
		return;
	for (const auto& entry : stdfs::directory_iterator(images))
		if (stdfs::is_directory(entry))
			allPacks.push_back(entry.path());
}

stdfs::path Texturepacks::findImage(const std::string& fileName)
{
	for (const auto& folder : activePacks)
	{
		const stdfs::path path = folder / fileName;
		if (stdfs::exists(path))
			return path;
	}
	return vanilla / fileName;
}


void Texturepacks::pushActivePack(const std::string& packName)
{
	stdfs::path path = images / packName;
	if (stdfs::exists(path) && stdfs::is_directory(path))
		activePacks.push_back(path);
}

void Texturepacks::removeActivePack(const std::string& packName)
{
	stdfs::path path = images / packName;
	const auto& it = std::remove_if(activePacks.begin(), activePacks.end(), [&](const auto& pack) { return pack == path; });
	activePacks.erase(it, activePacks.end());
}

void Texturepacks::resetActivePacks()
{
	activePacks.clear();
	activePacks.push_back(vanilla);
}
