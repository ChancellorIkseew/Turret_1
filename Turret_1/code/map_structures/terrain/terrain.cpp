
#include <iostream>
#include <fstream>
#include <string>
#include <SFML\Graphics.hpp>

#include "terrain.h"

#include "map_structures/pre-settings/pre-settings.h"
#include "map_structures/base_engine/tile_coord.h"

#include "game_interface/gameplay/gameplay_util/camera.h"


TerrainMap::TerrainMap(const TileCoord mapSize)
{
	mapSizeX = mapSize.x;
	mapSizeY = mapSize.y;

	terrainMap.resize(mapSizeX);
	terrainMap.reserve(mapSizeX);
	for (int x = 0; x < mapSizeX; ++x)
	{
		terrainMap[x].resize(mapSizeY);
		terrainMap[x].reserve(mapSizeY);
		for (int y = 0; y < mapSizeY; ++y)
		{
			terrainMap[x][y] = std::make_unique<int>(0);
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
	for(int y = 0; y < mapSizeY; ++y)
	{
		for(int x = 0; x < mapSizeX; ++x)
		{
			terrainMap[x][y] = std::move(std::make_unique<int>(TILE_GROUND));
		
			int allRes = rand() %10;
		
			if(allRes == 9)
			{
				int oneRes = rand() %7;
				*terrainMap[x][y] = int(oneRes);
			}
		}
	}
	
	for(int k = 0; k < 2; ++k)
	{
		for(int y = 1; y < mapSizeY-2; ++y)
		{
			for(int x = 1; x < mapSizeX-2; ++x)
			{
				if(*terrainMap[x][y] != TILE_GROUND)
				{
					int dir = rand() %4;
					if(dir == 3)
						*terrainMap[x][y+1] = *terrainMap[x][y];
					else if(dir == 2)
						*terrainMap[x][y-1] = *terrainMap[x][y];
					else if(dir == 1)
						*terrainMap[x+1][y] = *terrainMap[x][y];
					else if(dir == 0)
						*terrainMap[x-1][y] = *terrainMap[x][y];
				}
			}
		}
	}
}



void TerrainMap::loadMap(const std::string& folder)
{
	std::string file = "saves/" + folder + "/terrain.txt";
	std::ifstream fin;
	fin.open(file);
	if(fin.is_open())
	{
		for(int y=0; y < mapSizeY; ++y)
		{
			for(int x=0; x < mapSizeX; ++x)
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
		for (int y = 0; y < mapSizeY; ++y)
		{
			for (int x = 0; x < mapSizeX; ++x)
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
