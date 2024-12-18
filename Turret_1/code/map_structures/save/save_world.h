#pragma once
#ifndef SAVE_WORLD_H
#define SAVE_WORLD_H

#include <fstream>
#include <cereal/cereal.hpp>
#include <cereal/archives/binary.hpp>

#include "map_structures/terrain/terrain.h"

class SaveWorld
{
private:

public:
	static void save(const std::string& saveFileName)
	{
		std::ofstream fout(saveFileName, std::ios::binary);
		cereal::BinaryOutputArchive archive(fout);
		TerrainMap::save(archive);
		fout.close();
	}

	static void load(const std::string& saveFileName)
	{
		std::ifstream fin(saveFileName, std::ios::binary);
		cereal::BinaryInputArchive archive(fin);
		TerrainMap::load(archive);
		fin.close();
	}

};

#endif // SAVE_WORLD_H
