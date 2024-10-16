
#include <iostream>
#include <SFML\Graphics.hpp>

#include "building_panel.h"

#include "game_interface/gameplay/sub_windows/sub_windows_util/sub_windows_list.h"
#include "specifications_panel.h"

#include "map_structures/buildings/building/buildings_ico.h"
#include "map_structures/terrain/terrain.h"
#include "map_structures/buildings/buildings_map/buildings_map.h"
#include "map_structures/buildings/building/buildings_enum.h"
#include "map_structures/base_engine/tile_coord.h"
#include "map_structures/base_engine/t1_mutex.h"

using namespace t1::bc;

BuildingPanel::BuildingPanel() : SubWindow('s', 144, 192, 0, 0)
{
	isBuildingTypeSelected = false;
	newBuildingType = VOID_;
	direction = 'w';

	this->prepareInterfaceSprites();
	this->relocate(1000, 1000);
}


void BuildingPanel::prepareInterfaceSprites()
{
	t1::bc::initBuildingIco();
	buildingsImage.loadFromFile("images/buildings_map.bmp");
	buildingsImage.createMaskFromColor(sf::Color(0, 255, 0));
	buildingsTexture.loadFromImage(buildingsImage);
	buildExampleSprite.setTexture(buildingsTexture); //Building_example_on_coursor
	buildExampleSprite.setOrigin(_HALF_TILE_, _HALF_TILE_);
}



void BuildingPanel::interact(const sf::Vector2i& mouseCoord, const sf::Vector2f& mouseMapCoord)
{
	if (isBuildingTypeSelected && noSubWindowSelected(mouseCoord))
	{
		std::cout << "building_place_works: " << newBuildingType << '\n';
		TileCoord selectedTile = t1::be::tile(mouseMapCoord.x, mouseMapCoord.y);

		mtBuildings.lock();
		if (newBuildingType == REMOVE)
		{
			if (BuildingsMap::isTurretOnTile(selectedTile))
				BuildingsMap::removeTurret(selectedTile);
			else
				BuildingsMap::demolishBuilding(selectedTile);
		}
		else if (newBuildingType == AUTOCANNON_TURRET || newBuildingType == ROCKET_TURRET)
		{
			if (!BuildingsMap::isTurretOnTile(selectedTile))
				BuildingsMap::setTurret(newBuildingType, selectedTile);
		}
		else
		{
			BuildingsMap::constructBuilding(newBuildingType, direction, selectedTile);
		}
		mtBuildings.unlock();
	}
	
	
	if (BuildingPanel::getInstance().containsCoursor(mouseCoord))
	{
		for (auto it = buildingsIcoTable.begin(); it != buildingsIcoTable.end(); ++it)
		{
			it->second.icoSprite.setColor(sf::Color::White);
		}

		for (auto it = buildingsIcoTable.begin(); it != buildingsIcoTable.end(); ++it)
		{
			if (it->second.icoSprite.getGlobalBounds().contains(mouseCoord.x, mouseCoord.y))
			{
				buildExampleSprite.setTextureRect(it->second.texMapRect);
				it->second.icoSprite.setColor(sf::Color(0, 250, 0));
				oldBuildingType = newBuildingType;
				newBuildingType = it->first;
				isBuildingTypeSelected = true;
				if (oldBuildingType == newBuildingType)
				{
					isBuildingTypeSelected = false;
					newBuildingType = VOID_;
					for (auto it = buildingsIcoTable.begin(); it != buildingsIcoTable.end(); ++it)
					{
						it->second.icoSprite.setColor(sf::Color::White);
					}
				}
				return;
			}	
		}

		isBuildingTypeSelected = false;
	}
}



void BuildingPanel::relocate(int windowSizeX, int windowSizeY)
{
	positionX = windowSizeX - sizeX;
	positionY = windowSizeY - sizeY;
    

	buildingsIcoTable[REMOVE].icoSprite.setPosition(windowSizeX - 82, windowSizeY - 182);

	buildingsIcoTable[STONE_TOWER].icoSprite.setPosition(windowSizeX - 134, windowSizeY - 182);
	buildingsIcoTable[STONE_WALL].icoSprite.setPosition(windowSizeX - 108, windowSizeY - 182);
	
	buildingsIcoTable[SMALL_DRILL].icoSprite.setPosition(windowSizeX - 134, windowSizeY - 156);
	buildingsIcoTable[BIG_DRILL].icoSprite.setPosition(windowSizeX - 108, windowSizeY - 156);
    
	buildingsIcoTable[SHELL_FACTORY].icoSprite.setPosition(windowSizeX - 134, windowSizeY - 104);
	buildingsIcoTable[ROCKET_FACTORY].icoSprite.setPosition(windowSizeX - 92, windowSizeY - 104);
    
	buildingsIcoTable[COAL_GENERATOR].icoSprite.setPosition(windowSizeX - 50, windowSizeY - 156);
    
	buildingsIcoTable[STANDARD_CONVEYER].icoSprite.setPosition(windowSizeX - 134, windowSizeY - 60);
	buildingsIcoTable[SHIELDED_CONVEYER].icoSprite.setPosition(windowSizeX - 108, windowSizeY - 60);

	buildingsIcoTable[BRIDGE].icoSprite.setPosition(windowSizeX - 82, windowSizeY - 60);
	buildingsIcoTable[ROUTER].icoSprite.setPosition(windowSizeX - 56, windowSizeY - 60);
	buildingsIcoTable[SORTER].icoSprite.setPosition(windowSizeX - 30, windowSizeY - 60);

	buildingsIcoTable[AUTOCANNON_TURRET].icoSprite.setPosition(windowSizeX - 56, windowSizeY - 182);
	buildingsIcoTable[ROCKET_TURRET].icoSprite.setPosition(windowSizeX - 30, windowSizeY - 182);
}



void BuildingPanel::draw(sf::RenderWindow& window)
{
	if (isBuildingTypeSelected)
	{
		SpecificationsPanel::getInstance().interact(newBuildingType);
		SpecificationsPanel::getInstance().draw(window);
	}

	this->drawSubWindowBase(window);

	for (auto it = buildingsIcoTable.cbegin(); it != buildingsIcoTable.cend(); ++it )
	{
		window.draw(it->second.icoSprite);
	}
}



void BuildingPanel::drawBuildExample(sf::RenderWindow& window, const sf::Vector2f& mouseMapCoord)
{
	if (isBuildingTypeSelected)
	{
		if (newBuildingType != STANDARD_CONVEYER && newBuildingType != SHIELDED_CONVEYER &&
			newBuildingType != BRIDGE && newBuildingType != SORTER)
		{
			direction = 'w';
			buildExampleSprite.setRotation(0);
		}
		buildExampleSprite.setPosition(mouseMapCoord);
		window.draw(buildExampleSprite);
	}
}



void BuildingPanel::rotateBuilding()
{
	switch (newBuildingType)
	{
	case STANDARD_CONVEYER:
	case SHIELDED_CONVEYER:
	case BRIDGE:
	case SORTER:
		if (direction == 'w')
		{
			direction = 'a';
			buildExampleSprite.setRotation(270);
		}
		else if (direction == 'a')
		{
			direction = 's';
			buildExampleSprite.setRotation(180);
		}
		else if (direction == 's')
		{
			direction = 'd';
			buildExampleSprite.setRotation(90);
		}
		else if (direction == 'd')
		{
			direction = 'w';
			buildExampleSprite.setRotation(0);
		}
		break;

	default:
		direction = 'w';
		buildExampleSprite.setRotation(0);
		break;
	}
}
