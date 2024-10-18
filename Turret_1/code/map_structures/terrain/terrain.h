#pragma once
#ifndef TERRAIN_MAP_H
#define TERRAIN_MAP_H

#include <string>
#include <SFML\Graphics.hpp>

#include "map_structures/base_engine/tile_coord.h"


class TerrainMap
{
private:	
	static inline TileCoord mapSize;
	static inline std::vector<std::vector<std::unique_ptr<int>>> terrainMap;
	
	static inline sf::Image terrainImage;
	static inline sf::Texture terrainTexture;
	static inline sf::Sprite mapSprite;
	
public:
	TerrainMap(const TileCoord mapSize);
	~TerrainMap();
	
	static void saveMap(const std::string& folder);
	static void loadMap(const std::string& folder);

	static void generateMap(); //empty constructor
	
	static int getTileType(int tileX, int tileY);
	
	static void prepareSprites();
	static void drawMap(sf::RenderWindow& window);
	
};


enum TerrainTiles
{
	TILE_GROUND = 0,
	TILE_STONE = 1,
	TILE_IRON = 2,
	TILE_COPPER = 3,
	TILE_SILICON = 4,
	TILE_COAL = 5,
	TILE_SULFUR = 6,
	TILE_SAND = 7,
	TILE_VATER = 21,
	TILE_OIL = 22

};


#endif // TERRAIN_MAP_H
