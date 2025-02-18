
#include <iostream>
#include <SFML\Graphics.hpp>
#include <cereal/cereal.hpp>
#include <cereal/archives/binary.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/memory.hpp>

#include "terrain.h"

#include "terrain_enum.h"
#include "terrain_generator.h"
#include "map_structures/pre-settings/pre-settings.h"
#include "map_structures/base_engine/base_engine.h"

#include "game_interface/gameplay/gameplay_util/camera.h"


TerrainMap::TerrainMap(const TileCoord mapSize)
{
	this->mapSize = mapSize;

	terrainMap.resize(mapSize.x);
	terrainMap.reserve(mapSize.x);
	for (auto& line : terrainMap)
	{
		line.resize(mapSize.y);
		line.reserve(mapSize.y);
		for (auto& terrain : line)
		{
			terrain = std::make_unique<int>(0);
		}
	}
}

void TerrainMap::save(cereal::BinaryOutputArchive& archive) const
{
	std::cout << "try save terrain_map\n";
	archive(terrainMap);
	std::cout << "save terrain_map works\n";
}

void TerrainMap::load(cereal::BinaryInputArchive& archive)
{
	std::cout << "try load terrain_map\n";
	archive(terrainMap);
	std::cout << "load terrain_map works\n";
}

void TerrainMap::generate(const TerrainPre& terrainPre)
{
	terrainMap = std::move(generateTerrain(terrainPre));
}


int TerrainMap::getTileType(int tileX, int tileY)
{
	return *terrainMap[tileX][tileY];
}


void TerrainMap::prepareSprites()
{
	terrainImage.loadFromFile("images/terrain.bmp");
	terrainTexture.loadFromImage(terrainImage);
	mapSprite.setTexture(terrainTexture);
}
	
void TerrainMap::draw(sf::RenderWindow& window, const Camera& camera)
{
	const TileCoord start = camera.getStartTile();
	const TileCoord end = camera.getEndTile();

	for (int y = start.y; y < end.y; ++y)
	{
		for (int x = start.x; x < end.x; ++x)
		{
			switch (*terrainMap[x][y])
			{
			case TILE_GROUND:
				mapSprite.setTextureRect(sf::IntRect(0, 0, _TILE_, _TILE_));	//void
				break;
			case TILE_STONE:
				mapSprite.setTextureRect(sf::IntRect(32, 0, _TILE_, _TILE_));	//stone
				break;
			case TILE_IRON:
				mapSprite.setTextureRect(sf::IntRect(64, 0, _TILE_, _TILE_));	//iron
				break;
			case TILE_COPPER:
				mapSprite.setTextureRect(sf::IntRect(96, 0, _TILE_, _TILE_));	//copper
				break;
			case TILE_SILICON:
				mapSprite.setTextureRect(sf::IntRect(0, 32, _TILE_, _TILE_));	//silicon
				break;
			case TILE_COAL:
				mapSprite.setTextureRect(sf::IntRect(32, 32, _TILE_, _TILE_));	//coal
				break;
			case TILE_SULFUR:
				mapSprite.setTextureRect(sf::IntRect(64, 32, _TILE_, _TILE_));	//sulfur
				break;
			}

			mapSprite.setPosition(x * _TILE_, y * _TILE_);
			window.draw(mapSprite);
		}
	}
}
