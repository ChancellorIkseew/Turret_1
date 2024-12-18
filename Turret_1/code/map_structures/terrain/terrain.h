#pragma once
#ifndef TERRAIN_MAP_H
#define TERRAIN_MAP_H

#include <SFML\Graphics.hpp>
#include <cereal/archives/binary.hpp>
#include "map_structures/base_engine/base_engine.h"


class TerrainMap
{
private:	
	TileCoord mapSize = TileCoord(0, 0);
	std::vector<std::vector<std::unique_ptr<int>>> terrainMap;
	
	static inline sf::Image terrainImage;
	static inline sf::Texture terrainTexture;
	static inline sf::Sprite mapSprite;
	
public:
	TerrainMap() = default;
	TerrainMap(const TileCoord mapSize);
	~TerrainMap() = default;

	void save(cereal::BinaryOutputArchive& archive) const;
	void load(cereal::BinaryInputArchive& archive);

	void generate(); //empty constructor
	
	int getTileType(int tileX, int tileY);
	
	void prepareSprites();
	void draw(sf::RenderWindow& window);
	
};

#endif // TERRAIN_MAP_H
