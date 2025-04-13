
#include <iostream>
#include <SFML\Graphics.hpp>
#include <cereal/cereal.hpp>
#include <cereal/archives/binary.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/memory.hpp>

#include "terrain.h"

#include "terrain_enum.h"
#include "content/texturepacks.h"
#include "game_interface/gameplay/gameplay_util/camera.h"

static sf::Image terrainImage;
static sf::Texture terrainTexture;
//
static sf::Shader tileShader;
static sf::RenderStates renderStates;
static sf::VertexArray vertexArray;
static TileCoord cashedStart, cashedEnd;
constexpr float TILE_F = static_cast<float>(_TILE_);

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
	terrainImage.loadFromFile(Texturepacks::findImage("terrain.bmp"));
	terrainTexture.loadFromImage(terrainImage);
	tileShader.loadFromFile("shaders/tile.frag", sf::Shader::Type::Fragment);
	tileShader.setUniform("tileset", terrainTexture);
	tileShader.setUniform("tile_size", sf::Glsl::Vec2(32.0f, 32.0f));
	tileShader.setUniform("atlas_size", sf::Glsl::Vec2(128.0f, 96.0f));
}


void TerrainMap::draw(sf::RenderWindow& window, const Camera& camera)
{
	const TileCoord start = camera.getStartTile();
	const TileCoord end = camera.getEndTile();
	
	if (cashedStart != start || cashedEnd != end)
	{
		cashedStart = start;
		cashedEnd = end;
		vertexArray.clear();
		vertexArray.setPrimitiveType(sf::PrimitiveType::Triangles);
		for (int y = start.y; y < end.y; ++y)
		{
			for (int x = start.x; x < end.x; ++x)
			{
				const float xPos = x * _TILE_;
				const float yPos = y * _TILE_;

				sf::Color tileColor; // Color is used as terrain and resource type
				tileColor.r = static_cast<uint8_t>(*terrainMap[x][y]);
				//tileColor.g = ;

				vertexArray.append({ {xPos, yPos}, tileColor, {0.f, 0.f} });
				vertexArray.append({ {xPos + TILE_F, yPos}, tileColor, {32.f, 0.f} });
				vertexArray.append({ {xPos + TILE_F, yPos + TILE_F}, tileColor, {32.f, 32.f} });
				vertexArray.append({ {xPos, yPos}, tileColor, {0.f, 0.f} });
				vertexArray.append({ {xPos + TILE_F, yPos + TILE_F}, tileColor, {32.f, 32.f} });
				vertexArray.append({ {xPos, yPos + TILE_F}, tileColor, {0.f, 32.f} });
			}
		}
	}
	
	renderStates.shader = &tileShader;
	renderStates.texture = &terrainTexture;
	window.draw(vertexArray, renderStates);
}
