#pragma once
#ifndef TERRAIN_MAP_H
#define TERRAIN_MAP_H

#include <SFML\Graphics.hpp>
#include <cereal/archives/binary.hpp>
#include "map_structures/base_engine/base_engine.h"


class TerrainMap
{
private:	
	static inline TileCoord mapSize;
	static inline std::vector<std::vector<std::unique_ptr<int>>> terrainMap;
	
	static inline sf::Image terrainImage;
	static inline sf::Texture terrainTexture;
	static inline sf::Sprite mapSprite;
	
public:
	TerrainMap() = default;
	TerrainMap(const TileCoord mapSize);
	~TerrainMap();

	static void save(cereal::BinaryOutputArchive& archive);
	static void load(cereal::BinaryInputArchive& archive);

	static void generateMap(); //empty constructor
	
	static int getTileType(int tileX, int tileY);
	
	static void prepareSprites();
	static void drawMap(sf::RenderWindow& window);
	
};

#endif // TERRAIN_MAP_H
