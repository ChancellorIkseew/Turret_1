
#include <iostream>
#include <SFML\Graphics.hpp>
#include <cereal/cereal.hpp>
#include <cereal/archives/binary.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/memory.hpp>

#include "terrain.h"

#include "terrain_enum.h"
#include "map_structures/pre-settings/pre-settings.h"

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


ResType TerrainMap::getTileType(const TileCoord tile) const
{
	return static_cast<ResType>(*terrainMap[tile.x][tile.y]);
}


void TerrainMap::prepareSprites()
{
	terrainImage.loadFromFile("images/terrain.bmp");
	terrainTexture.loadFromImage(terrainImage);
}


static TileCoord cameraStart, cameraEnd;
constexpr sf::Color WHITE = sf::Color::White;

void TerrainMap::draw(sf::RenderWindow& window, const Camera& camera) {
	const TileCoord start = camera.getStartTile();
	const TileCoord end = camera.getEndTile();
	if (cameraStart != start || cameraEnd != end)
	{
		cameraStart = start;
		cameraEnd = end;
		sf::Vector2f textureCoord;
		for (auto& [_, vertexArray] : tileVertexArrays)
			vertexArray.clear();

		for (int y = start.y; y < end.y; ++y)
		{
			for (int x = start.x; x < end.x; ++x)
			{
				const int tileType = *terrainMap[x][y];
				if (tileVertexArrays.find(tileType) == tileVertexArrays.end())
					tileVertexArrays[tileType] = sf::VertexArray(sf::PrimitiveType::Triangles);

				const int xPos = x * _TILE_;
				const int yPos = y * _TILE_;

				switch (tileType)
				{
				case TILE_GROUND:   textureCoord = sf::Vector2f(0.0f, 0.0f);   break;
				case TILE_STONE:    textureCoord = sf::Vector2f(32.0f, 0.0f);  break;
				case TILE_IRON:     textureCoord = sf::Vector2f(64.0f, 0.0f);  break;
				case TILE_COPPER:   textureCoord = sf::Vector2f(96.0f, 0.0f);  break;
				case TILE_SILICON:  textureCoord = sf::Vector2f(0.0f, 32.0f);  break;
				case TILE_COAL:     textureCoord = sf::Vector2f(32.0f, 32.0f); break;
				case TILE_SULFUR:   textureCoord = sf::Vector2f(64.0f, 32.0f); break;
				default:			textureCoord = sf::Vector2f(0.0f, 0.0f);   break;
				}

				sf::VertexArray& currentVA = tileVertexArrays[tileType];
				currentVA.append({ sf::Vector2f(xPos, yPos), WHITE, textureCoord });
				currentVA.append({ sf::Vector2f(xPos + _TILE_, yPos),  WHITE, sf::Vector2f(textureCoord.x + _TILE_, textureCoord.y) });
				currentVA.append({ sf::Vector2f(xPos + _TILE_, yPos + _TILE_),  WHITE, sf::Vector2f(textureCoord.x + _TILE_, textureCoord.y + _TILE_) });
				currentVA.append({ sf::Vector2f(xPos, yPos), sf::Color::White, textureCoord });
				currentVA.append({ sf::Vector2f(xPos + _TILE_, yPos + _TILE_),  WHITE, sf::Vector2f(textureCoord.x + _TILE_, textureCoord.y + _TILE_) });
				currentVA.append({ sf::Vector2f(xPos, yPos + _TILE_),  WHITE, sf::Vector2f(textureCoord.x, textureCoord.y + _TILE_) });
			}
		}
	}
	sf::RenderStates states;
	states.texture = &terrainTexture;
	for (auto& [_, vertexArray] : tileVertexArrays)
		window.draw(vertexArray, states);
}
