
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


TerrainMap::TerrainMap(const TileCoord mapSize) : mapSize(mapSize)
{
	terrainMap.resize(mapSize.x);
	for (auto& line : terrainMap)
		line.resize(mapSize.y);
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

void TerrainMap::generate(TerrainPre& terrainPre)
{
	terrainMap = std::move(generateTerrain(terrainPre));
}


ResType TerrainMap::getTileType(const TileCoord tile) const
{
	return static_cast<ResType>(*terrainMap[tile.x][tile.y]);
}


void TerrainMap::prepareSprites()
{
	terrainImage.loadFromFile("images/terrain.bmp");
	terrainTexture.loadFromImage(terrainImage);
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
				mapSprite.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), X1_RECT));	//void
				break;
			case TILE_STONE:
				mapSprite.setTextureRect(sf::IntRect(sf::Vector2i(32, 0), X1_RECT));	//stone
				break;
			case TILE_IRON:
				mapSprite.setTextureRect(sf::IntRect(sf::Vector2i(64, 0), X1_RECT));	//iron
				break;
			case TILE_COPPER:
				mapSprite.setTextureRect(sf::IntRect(sf::Vector2i(96, 0), X1_RECT));	//copper
				break;
			case TILE_SILICON:
				mapSprite.setTextureRect(sf::IntRect(sf::Vector2i(0, 32), X1_RECT));	//silicon
				break;
			case TILE_COAL:
				mapSprite.setTextureRect(sf::IntRect(sf::Vector2i(32, 32), X1_RECT));	//coal
				break;
			case TILE_SULFUR:
				mapSprite.setTextureRect(sf::IntRect(sf::Vector2i(64, 32), X1_RECT));	//sulfur
				break;
			}

			mapSprite.setPosition(sf::Vector2f(static_cast<float>(x * _TILE_), static_cast<float>(y * _TILE_)));
			window.draw(mapSprite);
		}
	}
}
