
#include <iostream>
#include <SFML\Graphics.hpp>

#include "building_panel.h"

#include "game_interface/sub_window/sub_win_util/sub_windows_list.h"
#include "specifications_panel.h"

#include "map_structures/buildings/building/buildings_ico.h"
#include "map_structures/terrain/terrain.h"
#include "map_structures/buildings/buildings_map/buildings_map.h"
#include "map_structures/buildings/building/buildings_enum.h"
#include "map_structures/base_engine/tile_coord.h"
#include "t1_system/t1_mutex.h"

//using namespace t1::bc;

BuildingPanel::BuildingPanel() : SubWindow('s', sf::Vector2u (144, 192), sf::Vector2u(0, 0))
{
	isBuildingTypeSelected = false;
	newBuildingType = VOID_;
	direction = 'w';

	this->prepareInterfaceSprites();
	this->relocate({ 0, 0 });
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



void BuildingPanel::interact(const sf::Vector2i& mouseCoord, const sf::Vector2f& mouseMapCoord, Team* team)
{
	if (isBuildingTypeSelected && noSubWindowSelected(mouseCoord))
	{
		std::cout << "building_place_works: " << newBuildingType << '\n';
		TileCoord selectedTile = t1::be::tile(mouseMapCoord.x, mouseMapCoord.y);

		t1::system::mt::buildings.lock();
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
				BuildingsMap::setTurret(newBuildingType, selectedTile, team);
		}
		else
		{
			BuildingsMap::constructBuilding(newBuildingType, direction, selectedTile, team);
		}
		t1::system::mt::buildings.unlock();
	}
	
	
	if (BuildingPanel::getInstance().containsCoursor(mouseCoord))
	{
		for (auto& ico : t1::bc::buildingsIcoTable)
		{
			ico.second.icoSprite.setColor(sf::Color::White);
		}

		for (auto& ico : t1::bc::buildingsIcoTable)
		{
			if (ico.second.icoSprite.getGlobalBounds().contains(mouseCoord.x, mouseCoord.y))
			{
				buildExampleSprite.setTextureRect(ico.second.texMapRect);
				ico.second.icoSprite.setColor(sf::Color(0, 250, 0));
				oldBuildingType = newBuildingType;
				newBuildingType = ico.first;
				isBuildingTypeSelected = true;
				if (oldBuildingType == newBuildingType)
				{
					isBuildingTypeSelected = false;
					newBuildingType = VOID_;
					for (auto& ico : t1::bc::buildingsIcoTable)
					{
						ico.second.icoSprite.setColor(sf::Color::White);
					}
				}
				return;
			}	
		}

		isBuildingTypeSelected = false;
	}
}



void BuildingPanel::relocate(const sf::Vector2u windowSize)
{
	using namespace t1::bc;

	position = windowSize - size;

	buildingsIcoTable[REMOVE].icoSprite.setPosition(windowSize.x - 82, windowSize.y - 182);

	buildingsIcoTable[STONE_TOWER].icoSprite.setPosition(windowSize.x - 134, windowSize.y - 182);
	buildingsIcoTable[STONE_WALL].icoSprite.setPosition(windowSize.x - 108, windowSize.y - 182);
	
	buildingsIcoTable[SMALL_DRILL].icoSprite.setPosition(windowSize.x - 134, windowSize.y - 156);
	buildingsIcoTable[BIG_DRILL].icoSprite.setPosition(windowSize.x - 108, windowSize.y - 156);
    
	buildingsIcoTable[SHELL_FACTORY].icoSprite.setPosition(windowSize.x - 134, windowSize.y - 104);
	buildingsIcoTable[ROCKET_FACTORY].icoSprite.setPosition(windowSize.x - 92, windowSize.y - 104);
    
	buildingsIcoTable[COAL_GENERATOR].icoSprite.setPosition(windowSize.x - 50, windowSize.y - 156);
    
	buildingsIcoTable[STANDARD_CONVEYER].icoSprite.setPosition(windowSize.x - 134, windowSize.y - 60);
	buildingsIcoTable[SHIELDED_CONVEYER].icoSprite.setPosition(windowSize.x - 108, windowSize.y - 60);

	buildingsIcoTable[BRIDGE].icoSprite.setPosition(windowSize.x - 82, windowSize.y - 60);
	buildingsIcoTable[ROUTER].icoSprite.setPosition(windowSize.x - 56, windowSize.y - 60);
	buildingsIcoTable[SORTER].icoSprite.setPosition(windowSize.x - 30, windowSize.y - 60);

	buildingsIcoTable[AUTOCANNON_TURRET].icoSprite.setPosition(windowSize.x - 56, windowSize.y - 182);
	buildingsIcoTable[ROCKET_TURRET].icoSprite.setPosition(windowSize.x - 30, windowSize.y - 182);
}



void BuildingPanel::draw(sf::RenderWindow& window)
{
	if (isBuildingTypeSelected)
	{
		SpecificationsPanel::getInstance().interact(newBuildingType);
		SpecificationsPanel::getInstance().draw(window);
	}

	this->drawSubWindowBase(window);

	for (auto& ico : t1::bc::buildingsIcoTable)
	{
		window.draw(ico.second.icoSprite);
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
