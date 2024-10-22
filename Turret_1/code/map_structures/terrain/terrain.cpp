
#include <iostream>
#include <fstream>
#include <string>
#include <SFML\Graphics.hpp>

#include "terrain.h"

#include "terrain_enum.h"
#include "terrain_generator.h"
#include "map_structures/pre-settings/pre-settings.h"
#include "map_structures/base_engine/tile_coord.h"

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

	this->prepareSprites();
}

TerrainMap::~TerrainMap()
{
	terrainMap.clear();
}


void TerrainMap::generateMap() //empty constructor
{
	terrainMap = std::move(generateTerrain(PreSettings::getTerrain()));
}



void TerrainMap::loadMap(const std::string& folder)
{
	std::string file = "saves/" + folder + "/terrain.txt";
	std::ifstream fin;
	fin.open(file);
	if(fin.is_open())
	{
		for(int y=0; y < mapSize.y; ++y)
		{
			for(int x=0; x < mapSize.x; ++x)
			{
				char c; 
				fin.get(c);
				terrainMap[x][y] = std::move(std::make_unique<int>(c - 48));
			}
			char c;
			fin.get(c);
		}	
	}
	fin.close();
	std::cout << "load_terrain_map_works" << '\n';
}



int TerrainMap::getTileType(int tileX, int tileY)
{
	return *terrainMap[tileX][tileY];
}


void TerrainMap::saveMap(const std::string& folder)
{
	std::string file = "saves/" + folder + "/terrain.txt";
	std::ofstream fout;
	fout.open(file);
	if (fout.is_open())
	{
		for (int y = 0; y < mapSize.y; ++y)
		{
			for (int x = 0; x < mapSize.x; ++x)
			{
				fout << *terrainMap[x][y];
			}
			fout << '\n';
		}
	}
	fout.close();
	std::cout << "Save map terrain works" <<'\n';
}


void TerrainMap::prepareSprites()
{
	terrainImage.loadFromFile("images/terrain.bmp");
	terrainTexture.loadFromImage(terrainImage);
	mapSprite.setTexture(terrainTexture);
}
	
void TerrainMap::drawMap(sf::RenderWindow& window)
{
	int startX = Camera::startTile.x;
	int startY = Camera::startTile.y;

	int endX = Camera::endTile.x;
	int endY = Camera::endTile.y;

	for (int y = startY; y < endY; ++y)
	{
		for (int x = startX; x < endX; ++x)
		{
			switch (*terrainMap[x][y])
			{
			case TILE_GROUND:
			{
				mapSprite.setTextureRect(sf::IntRect(0, 0, _TILE_, _TILE_));	//void

				break;
			}

			case TILE_STONE:
			{
				mapSprite.setTextureRect(sf::IntRect(32, 0, _TILE_, _TILE_));	//stone

				break;
			}

			case TILE_IRON:
			{
				mapSprite.setTextureRect(sf::IntRect(64, 0, _TILE_, _TILE_));	//iron

				break;
			}

			case TILE_COPPER:
			{
				mapSprite.setTextureRect(sf::IntRect(96, 0, _TILE_, _TILE_));	//copper

				break;
			}

			case TILE_SILICON:
			{
				mapSprite.setTextureRect(sf::IntRect(0, 32, _TILE_, _TILE_));	//silicon

				break;
			}

			case TILE_COAL:
			{
				mapSprite.setTextureRect(sf::IntRect(32, 32, _TILE_, _TILE_));	//coal

				break;
			}

			case TILE_SULFUR:
			{
				mapSprite.setTextureRect(sf::IntRect(64, 32, _TILE_, _TILE_));	//sulfur

				break;
			}
			/*
			case '7':
				{
					terrainMap[i][j] = 0;
					//mapSprite.setTextureRect(sf::IntRect(48, 16, 16, 16));	//leaf

					break;
				}
			*/

			}

			mapSprite.setPosition(x * _TILE_, y * _TILE_);
			window.draw(mapSprite);
		}
	}
}
