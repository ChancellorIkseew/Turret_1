#pragma once
#ifndef T1_TEXTUREPACKS_H
#define T1_TEXTUREPACKS_H

#include <filesystem>

class Texturepacks
{
public:
	static void saveConfig();
	static void loadConfig();

	static void findPacks();
	static std::filesystem::path findImage(const std::string& fileName);

	static void pushActivePack(const std::string& packName);
	static void removeActivePack(const std::string& packName);
	static void clearActivePacks();

	static void loadTextures();

};

#endif // T1_TEXTUREPACKS_H
