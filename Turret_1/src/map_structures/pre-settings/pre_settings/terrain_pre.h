#pragma once
#ifndef MAP_STR_TERRAIN_PRE_H
#define MAP_STR_TERRAIN_PRE_H

#include <map>
#include <cpptoml.h>
#include "map_structures/base_engine/base_engine.h"
#include "map_structures/resources/res_enum.h"

struct TerrainPre
{
	uint32_t seed = 0;
	uint8_t smoothLayer = 0;
	std::map<ResType, int> frequency;
	std::map<ResType, int> depositSize;
	TileCoord mapSize = TileCoord(0, 0);

	void save(std::shared_ptr<cpptoml::table> root) const
	{
		auto table = cpptoml::make_table();
		table->insert("seed", seed);
		table->insert("map-size-x", mapSize.x);
		table->insert("map-size-y", mapSize.y);
		root->insert("terrain", table);
	}

	void load(std::shared_ptr<cpptoml::table> root)
	{
		const auto table = root->get_table("terrain");
		//
		seed = table->get_as<uint32_t>("seed").value_or(0);
		smoothLayer = table->get_as<uint8_t>("smooth-layer").value_or(0);
		mapSize.x = table->get_as<uint32_t>("map-size-x").value_or(100);
		mapSize.y = table->get_as<uint32_t>("map-size-y").value_or(100);
	}
};

#endif // MAP_STR_TERRAIN_PRE_H
