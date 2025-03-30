
#include "texturepacks.h"
#include <algorithm>
#include <vector>

namespace stdfs = std::filesystem;
static const stdfs::path images = "images";
static const stdfs::path vanilla = images / "vanilla";
static std::vector<stdfs::path> allPacks;
static std::vector<stdfs::path> activePacks;

void Texturepacks::findPacks()
{
	if (!stdfs::exists(images))
		return;
	for (const auto& entry : stdfs::directory_iterator(images))
		if (stdfs::is_directory(entry))
			allPacks.push_back(entry.path());
}

stdfs::path Texturepacks::findImage(const std::string fileName)
{
	for (const auto& folder : activePacks)
	{
		const stdfs::path path = folder / fileName;
		if (stdfs::exists(path))
			return path;
	}
	return vanilla / fileName;
}


void Texturepacks::pushActivePack(const std::string packName)
{
	stdfs::path path = images / packName;
	if (stdfs::exists(path) && stdfs::is_directory(path))
		activePacks.push_back(path);
}

void Texturepacks::removeActivePack(const std::string packName)
{
	stdfs::path path = images / packName;
	const auto& it = std::remove_if(activePacks.begin(), activePacks.end(), [&](const auto& pack) { return pack == path; });
	activePacks.erase(it, activePacks.end());
}

void Texturepacks::clearActivePacks()
{
	activePacks.clear();
	activePacks.push_back(vanilla);
}
