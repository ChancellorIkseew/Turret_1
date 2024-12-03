#pragma once
#ifndef TERRAIN_MAP_H
#define TERRAIN_MAP_H

#include <string>
#include <SFML\Graphics.hpp>

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
	TerrainMap(const TileCoord mapSize);
	~TerrainMap();
	
	static void saveMap(const std::string& folder);
	static void loadMap(const std::string& folder);

	static void generateMap(); //empty constructor
	
	static int getTileType(int tileX, int tileY);
	
	static void prepareSprites();
	static void drawMap(sf::RenderWindow& window);
	
};

#endif // TERRAIN_MAP_H
