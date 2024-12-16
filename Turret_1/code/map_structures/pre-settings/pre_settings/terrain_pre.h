#pragma once
#ifndef MAP_STR_TERRAIN_PRE_H
#define MAP_STR_TERRAIN_PRE_H

#include <map>
#include "util/parser/cpptoml.h"
#include "map_structures/base_engine/base_engine.h"

struct TerrainPre
{
	uint32_t seed;
	uint8_t smoothLayer;
	std::map<int, int> frequency;
	std::map<int, int> depositSize;
	TileCoord mapSize;

	void save(std::shared_ptr<cpptoml::table> root) const
	{
		auto mobsRoot = cpptoml::make_table();
		mobsRoot->insert("seed", seed);
		mobsRoot->insert("map-size-x", mapSize.x);
		mobsRoot->insert("map-size-y", mapSize.y);
		root->insert("terrain", mobsRoot);
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
