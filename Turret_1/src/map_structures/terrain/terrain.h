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

enum class TileType
{
	VOID = 0,
	SAND = 1,
	WATER = 2
};


class TerrainTile
{
private:
	TileType tileType = TileType::VOID;
	ResType resType = ResType::NO_RESOURCES;

public:
	TerrainTile(TileType tileType, ResType resType) :
		tileType(tileType), resType(resType) { }

	TileType getTileType() { return tileType; }
	ResType getResType() { return resType; }
};


class TerrainMap
{
private:	
	TileCoord mapSize;
	std::vector<std::vector<TerrainTile>> terrainMap;
	std::unordered_map<TileType, sf::VertexArray> tileVertexArrays;
	
	static inline sf::Image terrainImage;
	static inline sf::Texture terrainTexture;
	static inline sf::Sprite mapSprite = sf::Sprite(terrainTexture);
	
public:
	TerrainMap() = default;
	TerrainMap(const TileCoord mapSize);
	~TerrainMap() = default;

	void save(cereal::BinaryOutputArchive& archive) const;
	void load(cereal::BinaryInputArchive& archive);

	void generate(const TerrainPre& terrainPre); //empty constructor
	
	TerrainTile getTile(const TileCoord tile) const;
	
	static void prepareSprites();
	void draw(sf::RenderWindow& window, const Camera& camera);
	
};

#endif // TERRAIN_MAP_H
