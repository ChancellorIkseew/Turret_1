
#include <iostream>
#include <SFML\Graphics.hpp>

#include "building_panel.h"

#include "game_interface/gameplay/sub_windows/sub_windows_util/sub_windows_list.h"

#include "map_structures/terrain/terrain.h"
#include "map_structures/buildings/buildings_map.h"
#include "map_structures/buildings/building/buildings_enum.h"
#include "map_structures/base_engine/tile_coord.h"
#include "map_structures/base_engine/t1_mutex.h"


BuildingPanel::BuildingPanel() : SubWindow('s', 144, 192, 0, 0)
{
	//isBuildingTypeSelected = false;
	//buildingType = VOID_;
	direction = 'w';

	this->prepareInterfaceSprites();
	this->relocate(1000, 1000);
}


void BuildingPanel::prepareInterfaceSprites()
{
	buildingsImage.loadFromFile("images/buildings.bmp");				//Building Base_texture for all buildings
	buildingsImage.createMaskFromColor(sf::Color(0, 255, 0));
	buildingsTexture.loadFromImage(buildingsImage);

	buildExampleSprite.setTexture(buildingsTexture);					//Building_example_on_coursor
	buildExampleSprite.setOrigin(8, 8);
	
	towerButtonSprite.setTexture(buildingsTexture);						//Button_tower
	towerButtonSprite.setTextureRect(sf::IntRect(0,0,16,16));
	
	wallButtonSprite.setTexture(buildingsTexture);						//Button_wall
	wallButtonSprite.setTextureRect(sf::IntRect(16,0,16,16));
	
	smallDrillButtonSprite.setTexture(buildingsTexture);				//Button_small_drill
	smallDrillButtonSprite.setTextureRect(sf::IntRect(64,0,16,16));
	
	bigDrillButtonSprite.setTexture(buildingsTexture);					//Button_big_drill
	bigDrillButtonSprite.setTextureRect(sf::IntRect(0,80,32,32));
	
	shellFactoryButtonSprite.setTexture(buildingsTexture);					//Button_shell_factory
	shellFactoryButtonSprite.setTextureRect(sf::IntRect(32,112,32,32));
	
	rocketFactoryButtonSprite.setTexture(buildingsTexture);					//Button_rocket_factory
	rocketFactoryButtonSprite.setTextureRect(sf::IntRect(96,0,48,48));
	
	allocationNodeButtonSprite.setTexture(buildingsTexture);			//Button_allocation_node
	allocationNodeButtonSprite.setTextureRect(sf::IntRect(80,0,16,16));
	
	generatorButtonSprite.setTexture(buildingsTexture);					//Button_generator
	generatorButtonSprite.setTextureRect(sf::IntRect(0, 112, 32, 32));
	
	turretButtonSprite.setTexture(buildingsTexture);					//Button_autocannon_turret
	turretButtonSprite.setTextureRect(sf::IntRect(34, 18, 12, 20));
	
	rocketTurretButtonSprite.setTexture(buildingsTexture);				//Button_rocket_turret
	rocketTurretButtonSprite.setTextureRect(sf::IntRect(48, 16, 16, 18));
	
	removeBuildingButtonSprite.setTexture(buildingsTexture);			//Button_remove_building
	removeBuildingButtonSprite.setTextureRect(sf::IntRect(32,0,16,16));
	
	conveyerButtonSprite.setTexture(buildingsTexture);					//Button_conveyer
	conveyerButtonSprite.setTextureRect(sf::IntRect(0,144,16,16));
	
	shieldedConveyerButtonSprite.setTexture(buildingsTexture);					//Button_sheilded_conveyer
	shieldedConveyerButtonSprite.setTextureRect(sf::IntRect(64,144,16,16));
	
	intersectionButtonSprite.setTexture(buildingsTexture);					//Button_intersection
	intersectionButtonSprite.setTextureRect(sf::IntRect(32,64,16,16));
	
	routerButtonSprite.setTexture(buildingsTexture);					//Button_router
	routerButtonSprite.setTextureRect(sf::IntRect(32,48,16,16));
	
	sorterButtonSprite.setTexture(buildingsTexture);					//Button_sorter
	sorterButtonSprite.setTextureRect(sf::IntRect(48,48,16,16));
	
}



void BuildingPanel::interact(sf::Vector2i& mouseCoord, sf::Vector2f& mouseMapCoord, bool& isBuildingTypeSelected, int& buildingType)
{
	if (isBuildingTypeSelected)
	{
		if (noSubWindowSelected(mouseCoord))
		{	
			std::cout << '\n' << "building_place_works: " << buildingType << std::endl;
			int tileX = tile(mouseMapCoord.x);
			int tileY = tile(mouseMapCoord.y);

			mtBuildings.lock();
			if (buildingType == REMOVE)
			{
				if (BuildingsMap::isTurretOnTile(tileX, tileY))
					BuildingsMap::removeTurret(tileX, tileY);
				else
					BuildingsMap::demolishBuilding(tileX, tileY);
			}
			else if (buildingType == AUTOCANNON_TURRET || buildingType == ROCKET_TURRET)
			{
				if (!BuildingsMap::isTurretOnTile(tileX, tileY))
					BuildingsMap::setTurret(buildingType, tileX, tileY);
			}
			else
			{
				BuildingsMap::constructBuilding(buildingType, direction, tileX, tileY);
			}
			mtBuildings.unlock();
		}
	}
	
	
	if (towerButtonSprite.getGlobalBounds().contains(mouseCoord.x, mouseCoord.y))
	{
		std::cout << "tower select button works" << std::endl;
		towerButtonSprite.setColor(sf::Color(0, 250, 0));
		selectBuildingType(isBuildingTypeSelected);
		buildingType =STONE_TOWER;
	}
	
	if (wallButtonSprite.getGlobalBounds().contains(mouseCoord.x, mouseCoord.y))
	{
		std::cout << "wall select button works" << std::endl;
		wallButtonSprite.setColor(sf::Color(0, 250, 0));
		selectBuildingType(isBuildingTypeSelected);
		buildingType =STONE_WALL;
	}
	
	if (smallDrillButtonSprite.getGlobalBounds().contains(mouseCoord.x, mouseCoord.y))
	{
		std::cout << "small_drill select button works" << std::endl;
		smallDrillButtonSprite.setColor(sf::Color(0, 250, 0));
		selectBuildingType(isBuildingTypeSelected);
		buildingType =SMALL_DRILL;
	}
	
	if (bigDrillButtonSprite.getGlobalBounds().contains(mouseCoord.x, mouseCoord.y))
	{
		std::cout << "big_drill select button works" << std::endl;
		bigDrillButtonSprite.setColor(sf::Color(0, 250, 0));
		selectBuildingType(isBuildingTypeSelected);
		buildingType =BIG_DRILL;
	}
	
	if (shellFactoryButtonSprite.getGlobalBounds().contains(mouseCoord.x, mouseCoord.y))
	{
		std::cout << "shell_factory select button works" << std::endl;
		shellFactoryButtonSprite.setColor(sf::Color(0, 250, 0));
		selectBuildingType(isBuildingTypeSelected);
		buildingType =SHELL_FACTORY;
	}
	
	if (rocketFactoryButtonSprite.getGlobalBounds().contains(mouseCoord.x, mouseCoord.y))
	{
		std::cout << "rocket_factory select button works" << std::endl;
		rocketFactoryButtonSprite.setColor(sf::Color(0, 250, 0));
		selectBuildingType(isBuildingTypeSelected);
		buildingType =ROCKET_FACTORY;
	}
	
	if (allocationNodeButtonSprite.getGlobalBounds().contains(mouseCoord.x, mouseCoord.y))
	{
		std::cout << "allocation_node select button works" << std::endl;
		allocationNodeButtonSprite.setColor(sf::Color(0, 250, 0));
		selectBuildingType(isBuildingTypeSelected);
		buildingType ='6';
	}
	
	if (generatorButtonSprite.getGlobalBounds().contains(mouseCoord.x, mouseCoord.y))
	{
		std::cout << "coal_generator select button works" << std::endl;
		generatorButtonSprite.setColor(sf::Color(0, 250, 0));
		selectBuildingType(isBuildingTypeSelected);
		buildingType =COAL_GENERATOR;
	}
	
	if (turretButtonSprite.getGlobalBounds().contains(mouseCoord.x, mouseCoord.y))
	{
		std::cout << "autocannon_turret select button works" << std::endl;
		turretButtonSprite.setColor(sf::Color(0, 250, 0));
		selectBuildingType(isBuildingTypeSelected);
		buildingType =AUTOCANNON_TURRET;
	}
	
	if (rocketTurretButtonSprite.getGlobalBounds().contains(mouseCoord.x, mouseCoord.y))
	{
		std::cout << "rocket_turret select button works" << std::endl;
		rocketTurretButtonSprite.setColor(sf::Color(0, 250, 0));
		selectBuildingType(isBuildingTypeSelected);
		buildingType =ROCKET_TURRET;
	}
	
	if (removeBuildingButtonSprite.getGlobalBounds().contains(mouseCoord.x, mouseCoord.y))
	{
		std::cout << "<remove> select button works" << std::endl;
		removeBuildingButtonSprite.setColor(sf::Color(250, 0, 0));
		selectBuildingType(isBuildingTypeSelected);
		buildingType =REMOVE;
	}
	
	if (conveyerButtonSprite.getGlobalBounds().contains(mouseCoord.x, mouseCoord.y))
	{
		std::cout << "conveyer select button works" << std::endl;
		conveyerButtonSprite.setColor(sf::Color(0, 250, 0));
		selectBuildingType(isBuildingTypeSelected);
		buildingType =STANDARD_CONVEYER_UP;
	}
	
	if (shieldedConveyerButtonSprite.getGlobalBounds().contains(mouseCoord.x, mouseCoord.y))
	{
		std::cout << "shielded_conveyer select button works" << std::endl;
		shieldedConveyerButtonSprite.setColor(sf::Color(0, 250, 0));
		selectBuildingType(isBuildingTypeSelected);
		buildingType =SHIELDED_CONVEYER_UP;
	}
	
	if (intersectionButtonSprite.getGlobalBounds().contains(mouseCoord.x, mouseCoord.y))
	{
		std::cout << "intersection select button works" << std::endl;
		intersectionButtonSprite.setColor(sf::Color(0, 250, 0));
		selectBuildingType(isBuildingTypeSelected);
		buildingType = BRIDGE;
	}
	
	if (routerButtonSprite.getGlobalBounds().contains(mouseCoord.x, mouseCoord.y))
	{
		std::cout << "router select button works" << std::endl;
		routerButtonSprite.setColor(sf::Color(0, 250, 0));
		selectBuildingType(isBuildingTypeSelected);
		buildingType =ROUTER;
	}
	
	if (sorterButtonSprite.getGlobalBounds().contains(mouseCoord.x, mouseCoord.y))
	{
		std::cout << "sorter select button works" << std::endl;
		sorterButtonSprite.setColor(sf::Color(0, 250, 0));
		selectBuildingType(isBuildingTypeSelected);
		buildingType =SORTER;
	}
	

	if (!isBuildingTypeSelected)
	{
		towerButtonSprite.setColor(sf::Color::White);
		wallButtonSprite.setColor(sf::Color::White);
		smallDrillButtonSprite.setColor(sf::Color::White);
		bigDrillButtonSprite.setColor(sf::Color::White);
		shellFactoryButtonSprite.setColor(sf::Color::White);
		rocketFactoryButtonSprite.setColor(sf::Color::White);
		allocationNodeButtonSprite.setColor(sf::Color::White);
		removeBuildingButtonSprite.setColor(sf::Color::White);
		generatorButtonSprite.setColor(sf::Color::White);
		turretButtonSprite.setColor(sf::Color::White);
		rocketTurretButtonSprite.setColor(sf::Color::White);
		conveyerButtonSprite.setColor(sf::Color::White);
		shieldedConveyerButtonSprite.setColor(sf::Color::White);
		intersectionButtonSprite.setColor(sf::Color::White);
		routerButtonSprite.setColor(sf::Color::White);
		sorterButtonSprite.setColor(sf::Color::White);
		
	}
}



void BuildingPanel::relocate(int windowSizeX, int windowSizeY)
{
	positionX = windowSizeX - sizeX;
	positionY = windowSizeY - sizeY;

	//std::cout << "BPX: " << positionX << " BPY:" << positionY << '\n';
    
    towerButtonSprite.setPosition(windowSizeX - 134, windowSizeY - 182);
    wallButtonSprite.setPosition(windowSizeX - 108, windowSizeY - 182);
    removeBuildingButtonSprite.setPosition(windowSizeX - 82, windowSizeY - 182);
    
    smallDrillButtonSprite.setPosition(windowSizeX - 134, windowSizeY - 156);
    bigDrillButtonSprite.setPosition(windowSizeX - 108, windowSizeY - 156);
    
    shellFactoryButtonSprite.setPosition(windowSizeX - 134, windowSizeY - 104);
    rocketFactoryButtonSprite.setPosition(windowSizeX - 92, windowSizeY - 104);
    
    allocationNodeButtonSprite.setPosition(windowSizeX - 134, windowSizeY - 130);
    generatorButtonSprite.setPosition(windowSizeX - 50, windowSizeY - 156);
    
    turretButtonSprite.setPosition(windowSizeX - 56, windowSizeY - 182);
    rocketTurretButtonSprite.setPosition(windowSizeX - 30, windowSizeY - 182);
    
    conveyerButtonSprite.setPosition(windowSizeX - 134, windowSizeY - 60);
    shieldedConveyerButtonSprite.setPosition(windowSizeX - 108, windowSizeY - 60);
    intersectionButtonSprite.setPosition(windowSizeX - 82, windowSizeY - 60);
    routerButtonSprite.setPosition(windowSizeX - 56, windowSizeY - 60);
    sorterButtonSprite.setPosition(windowSizeX - 30, windowSizeY - 60);
    
}



void BuildingPanel::draw(sf::RenderWindow& window)
{
	this->drawSubWindowBase(window);

	window.draw(towerButtonSprite);
	window.draw(wallButtonSprite);
	window.draw(removeBuildingButtonSprite);
	
	window.draw(smallDrillButtonSprite);
	window.draw(bigDrillButtonSprite);
	
	window.draw(shellFactoryButtonSprite);
	window.draw(rocketFactoryButtonSprite);
	
	window.draw(allocationNodeButtonSprite);
	window.draw(generatorButtonSprite);
	
	window.draw(turretButtonSprite);
	window.draw(rocketTurretButtonSprite);
	
	window.draw(conveyerButtonSprite);
	window.draw(shieldedConveyerButtonSprite);
	window.draw(intersectionButtonSprite);
	window.draw(routerButtonSprite);
	window.draw(sorterButtonSprite);
}



void BuildingPanel::drawBuildExample(sf::RenderWindow& window, sf::Vector2f mouseMapCoord, int buildingType)
{
	selectBuildingTexture(buildingType);

	buildExampleSprite.setPosition(mouseMapCoord.x, mouseMapCoord.y);
	window.draw(buildExampleSprite);
}



void BuildingPanel::selectBuildingType(bool& isBuildingTypeSelected)
{
	if (!isBuildingTypeSelected)
	{
		isBuildingTypeSelected = true;
	}
	else
	{
		isBuildingTypeSelected = false;
	}
}


void BuildingPanel::rotateBuilding(int& buildingType)
{
	switch (buildingType)
	{
	case STANDARD_CONVEYER_UP:
		buildingType = STANDARD_CONVEYER_LEFT;
		break;
	case STANDARD_CONVEYER_LEFT:
		buildingType = STANDARD_CONVEYER_DOWN;
		break;
	case STANDARD_CONVEYER_DOWN:
		buildingType = STANDARD_CONVEYER_RIGHT;
		break;
	case STANDARD_CONVEYER_RIGHT:
		buildingType = STANDARD_CONVEYER_UP;
		break;

	case SHIELDED_CONVEYER_UP:
		buildingType = SHIELDED_CONVEYER_LEFT;
		break;
	case SHIELDED_CONVEYER_LEFT:
		buildingType = SHIELDED_CONVEYER_DOWN;
		break;
	case SHIELDED_CONVEYER_DOWN:
		buildingType = SHIELDED_CONVEYER_RIGHT;
		break;
	case SHIELDED_CONVEYER_RIGHT:
		buildingType = SHIELDED_CONVEYER_UP;
		break;

	case BRIDGE:
	case SORTER:
		if (direction == 'w')
			direction = 'a';
		else if (direction == 'a')
			direction = 's';
		else if (direction == 's')
			direction = 'd';
		else if (direction == 'd')
			direction = 'w';
		break;

	default:
		break;
	}
}


void BuildingPanel::selectBuildingTexture(int buildingType)
{
	switch (buildingType)
	{
	case REMOVE:
		buildExampleSprite.setTextureRect(sf::IntRect(32, 0, 16, 16));	//cross_of_demolition
		break;
	
	case CORE_MK1:
		buildExampleSprite.setTextureRect(sf::IntRect(0, 48, 32, 32));	//core
		break;

	case STONE_TOWER:
		buildExampleSprite.setTextureRect(sf::IntRect(0, 0, 16, 16));	//tower
		break;

	case STONE_WALL:
		buildExampleSprite.setTextureRect(sf::IntRect(16, 0, 16, 16));	//wall
		break;

	case SMALL_DRILL:
		buildExampleSprite.setTextureRect(sf::IntRect(64, 0, 16, 16));	//small_drill
		break;

	case BIG_DRILL:
		buildExampleSprite.setTextureRect(sf::IntRect(0, 80, 32, 32));	//big_drill
		break;

	case SHELL_FACTORY:
		buildExampleSprite.setTextureRect(sf::IntRect(32, 112, 32, 32));	//shell_factory
		break;

	case ROCKET_FACTORY:
		buildExampleSprite.setTextureRect(sf::IntRect(96, 0, 48, 48));	//rocket_factory
		break;

	case '6':
		buildExampleSprite.setTextureRect(sf::IntRect(80, 0, 16, 16));	//allocation_node
		break;

	case COAL_GENERATOR:
		buildExampleSprite.setTextureRect(sf::IntRect(0, 112, 32, 32));	//generator
		break;

	case AUTOCANNON_TURRET:
		buildExampleSprite.setTextureRect(sf::IntRect(34, 18, 12, 20));	//autocannon_turret
		break;

	case ROCKET_TURRET:
		buildExampleSprite.setTextureRect(sf::IntRect(48, 16, 16, 18));	//rocket_turret
		break;

	case STANDARD_CONVEYER_UP:
		buildExampleSprite.setTextureRect(sf::IntRect(0, 144, 16, 16));	//conveyer
		break;

	case STANDARD_CONVEYER_LEFT:
		buildExampleSprite.setTextureRect(sf::IntRect(16, 144, 16, 16));	//conveyer
		break;

	case STANDARD_CONVEYER_DOWN:
		buildExampleSprite.setTextureRect(sf::IntRect(32, 144, 16, 16));	//conveyer
		break;

	case STANDARD_CONVEYER_RIGHT:
		buildExampleSprite.setTextureRect(sf::IntRect(48, 144, 16, 16));	//conveyer
		break;

	case SHIELDED_CONVEYER_UP:
		buildExampleSprite.setTextureRect(sf::IntRect(64, 144, 16, 16));	//shielded_conveyer
		break;

	case SHIELDED_CONVEYER_LEFT:
		buildExampleSprite.setTextureRect(sf::IntRect(80, 144, 16, 16));	//shielded_conveyer
		break;

	case SHIELDED_CONVEYER_DOWN:
		buildExampleSprite.setTextureRect(sf::IntRect(96, 144, 16, 16));	//shielded_conveyer
		break;

	case SHIELDED_CONVEYER_RIGHT:
		buildExampleSprite.setTextureRect(sf::IntRect(112, 144, 16, 16));	//shielded_conveyer
		break;

	case BRIDGE:
		buildExampleSprite.setTextureRect(sf::IntRect(32, 64, 16, 16));		//intersection
		break;

	case ROUTER:
		buildExampleSprite.setTextureRect(sf::IntRect(32, 48, 16, 16));		//router
		break;

	case SORTER:
		buildExampleSprite.setTextureRect(sf::IntRect(48, 48, 16, 16));		//sorter
		break;
	}

	switch (buildingType)
	{
	default:
		buildExampleSprite.setRotation(0);
		break;

	case BRIDGE:
	case SORTER:
		if (direction == 'w')
			buildExampleSprite.setRotation(0);
		else if (direction == 'a')
			buildExampleSprite.setRotation(270);
		else if (direction == 's')
			buildExampleSprite.setRotation(180);
		else if (direction == 'd')
			buildExampleSprite.setRotation(90);
		break;
	}
}
