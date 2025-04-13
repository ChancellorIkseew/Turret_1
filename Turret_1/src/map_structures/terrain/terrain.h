#pragma once
#ifndef TERRAIN_MAP_H
#define TERRAIN_MAP_H

#include <unordered_map>
#include <SFML\Graphics.hpp>
#include <cereal/archives/binary.hpp>
#include "map_structures/base_engine/base_engine.h"
#include "map_structures/resources/res_enum.h"

class Camera;
struct TerrainPre;

class TerrainMap
{
private:	
	TileCoord mapSize;
	std::vector<std::vector<std::unique_ptr<int>>> terrainMap;
	
public:
	TerrainMap() = default;
	TerrainMap(const TileCoord mapSize);
	~TerrainMap() = default;

	void save(cereal::BinaryOutputArchive& archive) const;
	void load(cereal::BinaryInputArchive& archive);

	void generate(const TerrainPre& terrainPre); //empty constructor
	
	ResType getTileType(const TileCoord tile) const;
	
	static void prepareSprites();
	void draw(sf::RenderWindow& window, const Camera& camera);
	
};

#endif // TERRAIN_MAP_H
