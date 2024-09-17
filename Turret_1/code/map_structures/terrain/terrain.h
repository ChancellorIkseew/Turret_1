#pragma once
#ifndef TERRAIN_MAP_H
#define TERRAIN_MAP_H

#include <string>
#include <SFML\Graphics.hpp>


class TerrainMap
{
private:	

	static inline int mapMaxX, mapMaxY;
	
	static inline std::string saveFileName;

	static inline int** arr;
	
	static inline sf::Image terrainImage;
	static inline sf::Texture terrainTexture;
	static inline sf::Sprite mapSprite;
	
public:
	
	TerrainMap(std::string saveFolderName);
	~TerrainMap();
	
	static void saveMap();
	static void loadMap();

	static void mapGeneration(); //empty constructor
	
	static char getTileType(int tileX, int tileY);

	static void Print();
	
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
