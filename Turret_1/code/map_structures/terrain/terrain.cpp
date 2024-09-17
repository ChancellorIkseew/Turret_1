
#include <iostream>
#include <fstream>
#include <string>
#include <SFML\Graphics.hpp>


#include "terrain.h"

#include "../pre-settings/pre-settings.h"
#include "../base_engine/tile_coord.h"

#include "../../game_interface/gameplay/gameplay_util/camera.h"


TerrainMap::TerrainMap(std::string saveFolderName)
{
	saveFileName = "saves/" + saveFolderName + "/terrain.txt";

	mapMaxX = PreSettings::getMapMaxX();
	mapMaxY = PreSettings::getMapMaxY();

	arr = new int* [mapMaxX];
	for (int x = 0; x < mapMaxX; ++x)
	{
		arr[x] = new int[mapMaxY];

		for (int y = 0; y < mapMaxY; ++y)
		{
			arr[x][y] = TILE_GROUND;
		}
	}

	this->prepareSprites();
}

TerrainMap::~TerrainMap()
{
	for (int x = 0; x < mapMaxX; ++x)
	{
		delete[] arr[x];
		arr[x] = nullptr;
	}
	delete[] arr;
	arr = nullptr;
}


void TerrainMap::mapGeneration() //empty constructor
{
	

	for(int y = 0; y < mapMaxY; ++y)
	{
		for(int x = 0; x < mapMaxX; ++x)
		{
			arr[x][y] = TILE_GROUND;
		
			int allRes = rand() %10;
		
			if(allRes == 9)
			{
				int oneRes = rand() %7;
			
				arr[x][y] = int(oneRes+ TILE_GROUND);
			}
		}
	}
	
	
	for(int k = 0; k < 2; ++k)
	{
		for(int y = 1; y < mapMaxY-2; ++y)
		{
			for(int x = 1; x < mapMaxX-2; ++x)
			{
				if(arr[x][y] != TILE_GROUND)
				{
					int i = rand() %4;
					if(i == 3)
					{
						arr[x][y+1] = arr[x][y];
					}
					
					if(i == 2)
					{
						arr[x][y-1] = arr[x][y];
					}
				
					if(i == 1)
					{
						arr[x+1][y] = arr[x][y];
					}
				
					if(i == 0)
					{
						arr[x-1][y] = arr[x][y];
					}
				}
			}
		}
	}
	
}



void TerrainMap::loadMap()
{
	std::ifstream fin;
	fin.open(saveFileName);
	
	if(fin.is_open())
	{
		for(int y=0; y < mapMaxY; ++y)
		{
			for(int x=0; x < mapMaxX+1; ++x)
			{
				char c; 
				fin.get(c);
				
				if(x != mapMaxX)
				{
					arr[x][y] = int(c - 48);
				}
			}
		}	
	}
	fin.close();
	std::cout << "load_terrain_map_works" << '\n';
}



char TerrainMap::getTileType(int tileX, int tileY)
{
	return arr[tileX][tileY];
}



void TerrainMap::Print()
{
	for(int y = 0; y < mapMaxY; ++y)
	{
		for(int x = 0; x < mapMaxX; ++x)
		{
			std::cout<< arr[x][y];
		}
	
		std::cout<<'\n';
	}
	std::cout<< "array end" <<'\n';
}



void TerrainMap::saveMap()
{
	std::ofstream fout;
	fout.open(saveFileName);
	
	for(int y = 0; y < mapMaxY; ++y)
	{
		for(int x = 0; x < mapMaxX; ++x)
		{
			fout<< arr[x][y];
		}
		fout<<'\n';
	}
	fout<< "array end" <<'\n';
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

			switch (arr[x][y])
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
					arr[i][j] = 0;
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
