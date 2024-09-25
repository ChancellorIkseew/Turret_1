
#include <iostream>
#include <fstream>
#include <string>
#include <SFML\Graphics.hpp>
#include <list>

#include "resource_units.h"

#include "game_interface/gameplay/gameplay_util/camera.h"

#include "map_structures/buildings/buildings_map.h"
#include "map_structures/buildings/building/buildings_enum.h"
#include "map_structures/base_engine/tile_coord.h"

#include "res_enum.h"
#include "resources.h"

using namespace t1::be;

ResourceUnit::ResourceUnit(int type, int coordX, int coordY, char motionDirection)
{
	resType = type;
	
	this->coordX = coordX;
	this->coordY = coordY;
	
	position = {0, 0, 0};
	changePosition();

	this->motionDirection = motionDirection;
	currentTile = motionDirection;
	
	isWasted = false;
	isMotionAvailable = true;
}


void ResourceUnit::save(std::ofstream& fout)
{
	fout << resType << " " << motionDirection << " " << position.position
		<< " " << isMotionAvailable << " " << currentTile << " " << coordX << " " << coordY << '\n';
	fout << "$\n";
}

void ResourceUnit::load(std::ifstream& fin)
{
	fin >> resType >> motionDirection >> position.position >> isMotionAvailable >> currentTile >> coordX >> coordY;
	position.tileX = tile(coordX);
	position.tileY = tile(coordY);
	isWasted = false;
	char specialSymbol;
	fin >> specialSymbol;
}

void ResourceUnit::interact(int time)
{
	if (time%2 == 0)
	{
		this->moveResourceUnit();

		currentTile = BuildingsMap::getBuildingType(tile(coordX, coordY));

		switch(currentTile)
		{
			case STANDARD_CONVEYER:
			case SHIELDED_CONVEYER:
			{
				char dir = BuildingsMap::getBuildingDirection(tile(coordX, coordY));

				if ((dir == 'w' || dir == 's') && int(coordX) % _TILE_ == _HALF_TILE_)
					motionDirection = dir;
				else if ((dir == 'a' || dir == 'd') && int(coordY) % _TILE_ == _HALF_TILE_)
					motionDirection = dir;
				break;
			}
			
			case CORE_MK1:
			case CORE_MK2:
			case CORE_MK3:
				isWasted = true;
				t1::res::sendToBalance(resType, 1);
				break;
			
			default: // factories_and_towers
				if (BuildingsMap::canAccept(resType, { tile(coordX), tile(coordY) }))
				{
					isWasted = true;
					BuildingsMap::addToInventory(resType, { tile(coordX), tile(coordY) });
				}
				break;

			case VOID_:
				isWasted = true;
				break;
		}
	}
}



void ResourceUnit::moveResourceUnit()
{
	if (changePosition())
	{
		//std::cout << "change position = true" << '\n';

		ResPosition nextPosition = getNextPosition();

		//std::cout << "new: " << newPosition.tileX << " " << newPosition.tileY << " " << newPosition.position << '\n';
		//std::cout << "old: " << tile(coordX) << " " << tile(coordY) << " " << position.position << '\n';

		if (BuildingsMap::canAccept(resType, { nextPosition.tileX, nextPosition.tileY }) && 
			BuildingsMap::isThisPositionFree({ nextPosition.tileX, nextPosition.tileY }, nextPosition.position))
		{
			isMotionAvailable = true;

			BuildingsMap::leavePosition({ tile(coordX), tile(coordY) }, position.position);
			BuildingsMap::takePosition({ nextPosition.tileX, nextPosition.tileY }, nextPosition.position);

			position = nextPosition;
			//std::cout << "motion enable" << '\n';
		}
		else
		{
			isMotionAvailable = false;
			//std::cout << "motion disable" << '\n';
		}
	}

	if (isMotionAvailable)
	{
		switch (motionDirection)
		{
		case 'w':
			coordY = coordY - 1;
			break;

		case 'a':
			coordX = coordX - 1;
			break;

		case 's':
			coordY = coordY + 1;
			break;

		case 'd':
			coordX = coordX + 1;
			break;
		}
	}
}



bool ResourceUnit::changePosition()
{
	int inTileCoordX = int(coordX) % _TILE_;
	int inTileCoordY = int(coordY) % _TILE_;

	//x_line

	if (inTileCoordX == 16 && inTileCoordY == 6)
	{
		position.position = 0;
		return true;
	}

	if (inTileCoordX == 16 && inTileCoordY == 16)
	{
		position.position = 1;
		return true;
	}

	if (inTileCoordX == 16 && inTileCoordY == 26)
	{
		position.position = 2;
		return true;
	}

	if (inTileCoordX == 6 && inTileCoordY == 16)
	{
		position.position = 3;
		return true;
	}

	if (inTileCoordX == 26 && inTileCoordY == 16)
	{
		position.position = 4;
		return true;
	}

	return false;
}



ResPosition ResourceUnit::getNextPosition()
{
	int t = BuildingsMap::getBuildingType(tile(coordX, coordY));

	switch (t)
	{
	case STANDARD_CONVEYER:
	case SHIELDED_CONVEYER:
		switch (BuildingsMap::getBuildingDirection(tile(coordX, coordY)))
		{
		case 'w':
			if (position.position == 2 || position.position == 3 || position.position == 4)
				return { tile(coordX), tile(coordY), 1 };
			if (position.position == 1)
				return { tile(coordX), tile(coordY), 0 };
			if (position.position == 0)
				return { tile(coordX), tile(coordY) - 1, 2 };
			break;

		case 'a':
			if (position.position == 0 || position.position == 2 || position.position == 4)
				return { tile(coordX), tile(coordY), 1 };
			if (position.position == 1)
				return { tile(coordX), tile(coordY), 3 };
			if (position.position == 3)
				return { tile(coordX) - 1, tile(coordY), 4 };
			break;

		case 's':
			if (position.position == 0 || position.position == 3 || position.position == 4)
				return { tile(coordX), tile(coordY), 1 };
			if (position.position == 1)
				return { tile(coordX), tile(coordY), 2 };
			if (position.position == 2)
				return { tile(coordX), tile(coordY) + 1, 0 };
			break;

		case 'd':
			if (position.position == 0 || position.position == 2 || position.position == 3)
				return { tile(coordX), tile(coordY), 1 };
			if (position.position == 1)
				return { tile(coordX), tile(coordY), 4 };
			if (position.position == 4)
				return { tile(coordX) + 1, tile(coordY), 3 };
			break;
		}
		break;

	default:
		return { 0,0,0 };
		
	}
}


void ResourceUnit::prepareSprites()
{
	resourcesImage.loadFromFile("images/resources.bmp");			//Resources
	resourcesImage.createMaskFromColor(sf::Color(0, 255, 0));
	resourcesTexture.loadFromImage(resourcesImage);
	resourceSprite.setTexture(resourcesTexture);
	resourceSprite.setOrigin(4.5, 4.5);
}


void ResourceUnit::draw(sf::RenderWindow &window)
{
	if (tile(coordX) >= Camera::startTile.x && tile(coordY) >= Camera::startTile.y &&
		tile(coordX) <= Camera::endTile.x && tile(coordY) <= Camera::endTile.y)
	{
		switch (resType)
		{
		case RES_STONE:
			resourceSprite.setTextureRect(sf::IntRect(9, 0, 9, 9));	//Stone
			break;

		case RES_IRON:
			resourceSprite.setTextureRect(sf::IntRect(18, 0, 9, 9));	//Iron
			break;

		case RES_COPPER:
			resourceSprite.setTextureRect(sf::IntRect(27, 0, 9, 9));	//Copper
			break;

		case RES_SILICON:
			resourceSprite.setTextureRect(sf::IntRect(36, 0, 9, 9));	//Silicon
			break;

		case RES_COAL:
			resourceSprite.setTextureRect(sf::IntRect(45, 0, 9, 9));	//Coal
			break;

		case RES_SULFUR:
			resourceSprite.setTextureRect(sf::IntRect(54, 0, 9, 9));	//Sulfur
			break;

		case RES_AC_SHELLS:
			resourceSprite.setTextureRect(sf::IntRect(0, 18, 9, 9));	//Shells
			break;

		case RES_ROCKET:
			resourceSprite.setTextureRect(sf::IntRect(9, 18, 9, 9));	//Rocket
			break;

		default:
			resType = RES_NO_RESOURCES;
			resourceSprite.setTextureRect(sf::IntRect(0, 0, 9, 9));	//Eror_case
			break;
		}

		resourceSprite.setPosition(coordX, coordY);
		window.draw(resourceSprite);
	}
}



int ResourceUnit::getType()
{
	return resType;
}

bool ResourceUnit::getIsWasted()
{
	return isWasted;
}



std::list<ResourceUnit*> resourceUnitsList;



void moveResUnitsList(int time)
{
	for (std::list<ResourceUnit*>::iterator it = resourceUnitsList.begin(); it != resourceUnitsList.end();)
	{
		if((*it)->getIsWasted() == true)
		{
			delete *it;
			it = resourceUnitsList.erase(it);
		}
		else
		{
			(*it)->interact(time);
			++it;
		}
	}
}



void drawResUnitsList(sf::RenderWindow &window)
{
	for (std::list<ResourceUnit*>::iterator it = resourceUnitsList.begin(); it != resourceUnitsList.end(); ++it)
	{
		(*it)->draw(window);
	}
}



void saveResUnitsList(std::string saveFolderName)
{
	std::string saveFileName = "saves/" + saveFolderName + "/res_units.txt";

	std::ofstream fout;
	fout.open(saveFileName);

	for (std::list<ResourceUnit*>::iterator it = resourceUnitsList.begin(); it != resourceUnitsList.end(); ++it)
	{
		(*it)->save(fout);
	}
	fout << '&';
	fout.close();

	std::cout << "Save res_units list works" << '\n';
}


void loadResUnitsList(std::string saveFolderName)
{
	std::string saveFileName = "saves/" + saveFolderName + "/res_units.txt";

	std::ifstream fin;
	fin.open(saveFileName);

	char nextSymbol = '&';

	if (fin.is_open())
	{
		while (true)
		{
			fin >> nextSymbol;
			if (nextSymbol != '&')
			{
				fin.seekg(-1, std::ios::cur);

				ResourceUnit* resUnit = new ResourceUnit();
				resUnit->load(fin);
				resourceUnitsList.push_back(resUnit);
			}
			else
			{
				break;
			}
		}
	}
	fin.close();

	std::cout << "Load res_units list works" << '\n';
}



void cleanResUnitsList()
{
	resourceUnitsList.clear();
}
