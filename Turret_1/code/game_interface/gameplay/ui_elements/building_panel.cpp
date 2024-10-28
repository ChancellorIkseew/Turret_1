
#include <iostream>

#include "building_panel.h"
#include "building_panel/buildings_pages.h"

#include "game_interface/gameplay/gameplay.h"
#include "game_interface/ui_window/sub_win_util/fonts.h"

#include "map_structures/terrain/terrain.h"
#include "map_structures/buildings/buildings_map/buildings_map.h"
#include "map_structures/buildings/building/buildings_enum.h"
#include "map_structures/base_engine/tile_coord.h"
#include "t1_system/t1_mutex.h"
#include "t1_system/system.h"
#include "t1_system/sleep.h"

enum Buttons
{
	LOGISTICS = 0,
	DRILLS = 1,
	FACTORIES = 2,
	ELECTRICS = 3,
	WALLS = 4,
	TURRETS = 5,
	SPECIAL = 6,
	STORAGES = 7,
};


BuildingPanel::BuildingPanel() : UIWindow(sf::Vector2u(324, 192), sf::Vector2u(0, 0))
{
	selectedPage = LOGISTICS;
	isBuildingTypeSelected = false;
	newBuildingType = VOID_;
	oldBuildingType = VOID_;
	direction = 'w';

	this->prepareInterfaceSprites();
	specificationsPanel = std::make_unique<SpecificationsPanel>();
}


void BuildingPanel::prepareInterfaceSprites()
{
	buildingsImage.loadFromFile("images/buildings_ico.bmp");
	buildingsImage.createMaskFromColor(sf::Color(0, 255, 0));
	buildingsTexture.loadFromImage(buildingsImage);
	buildExample.setTexture(buildingsTexture); //Building_example_on_coursor
	buildExample.setOrigin(_HALF_TILE_, _HALF_TILE_);

	int line1 = 240;
	int line2 = 282;
	remove = BuildingIco(REMOVE);
	remove.setPosition(sf::Vector2u(10, 10));

	buttons[LOGISTICS] = Button("building/logistics_ico.bmp", sf::Vector2i(32, 32), sf::Vector2i(line1, 10));
	buttons[DRILLS] = Button("building/drill_ico.bmp", sf::Vector2i(32, 32), sf::Vector2i(line1, 52));
	buttons[FACTORIES] = Button("building/factory_ico.bmp", sf::Vector2i(32, 32), sf::Vector2i(line1, 94));
	buttons[ELECTRICS] = Button("building/electrics_ico.bmp", sf::Vector2i(32, 32), sf::Vector2i(line1, 136));

	buttons[WALLS] = Button("building/wall_ico.bmp", sf::Vector2i(32, 32), sf::Vector2i(line2, 10));
	buttons[TURRETS] = Button("building/turret_ico.bmp", sf::Vector2i(32, 32), sf::Vector2i(line2, 52));
	buttons[SPECIAL] = Button("building/special_ico.bmp", sf::Vector2i(32, 32), sf::Vector2i(line2, 94));
	buttons[STORAGES] = Button("building/storage_ico.bmp", sf::Vector2i(32, 32), sf::Vector2i(line2, 136));

	t1::bc::initLogistics(pages[LOGISTICS]);
	t1::bc::initDrills(pages[DRILLS]);
	t1::bc::initFactories(pages[FACTORIES]);
	t1::bc::initElectrics(pages[ELECTRICS]);

	t1::bc::initWalls(pages[WALLS]);
	t1::bc::initTurrets(pages[TURRETS]);
	t1::bc::initSpecial(pages[SPECIAL]);
	t1::bc::initStorages(pages[STORAGES]);

	for (auto& pg : pages)
		t1::bc::arrangePage(pg.second);
}



void BuildingPanel::interact(const sf::Vector2i& mouseCoord, const sf::Vector2f& mouseMapCoord, Team* const team)
{
	if (LMB_Pressed && isBuildingTypeSelected && (*Gameplay::getInstance()).noSubWindowSelected(mouseCoord))
	{
		placeBuilding(mouseMapCoord, team);
		t1::system::sleep(150);
		return;
	}

	if (RMB_Pressed)
	{
		rotateBuilding();
		t1::system::sleep(150);
		return;
	}
	
	selectBuildingType(mouseCoord);
}



void BuildingPanel::relocate(const sf::Vector2u windowSize)
{
	position = windowSize - size;

	remove.relocateWithOwner(position);

	for (auto& btn : buttons)
		btn.second.relocateWithOwner(position);

	for (auto& pg : pages)
	{
		for (auto& ico : pg.second)
			ico.second.relocateWithOwner(position);
	}

	specificationsPanel->relocate(windowSize);
}



void BuildingPanel::draw(sf::RenderWindow& window)
{
	if (isBuildingTypeSelected)
	{
		specificationsPanel->interact(newBuildingType);
		specificationsPanel->draw(window);
	}

	drawBase(window);
	remove.draw(window);
	for (auto& btn : buttons)
		btn.second.draw(window);
	for (auto& ico : pages[selectedPage])
		ico.second.draw(window);
}



void BuildingPanel::drawBuildExample(sf::RenderWindow& window, const sf::Vector2f& mouseMapCoord, Team* const team)
{
	if (!isBuildingTypeSelected)
		return;
	if (newBuildingType != STANDARD_CONVEYER && newBuildingType != SHIELDED_CONVEYER &&
		newBuildingType != BRIDGE && newBuildingType != SORTER)
	{
		direction = 'w';
		buildExample.setRotation(0);
	}

	TileCoord selectedTile = t1::be::tile(mouseMapCoord.x, mouseMapCoord.y);
	if (BuildingsMap::isAvaluablePlaceBuilding(newBuildingType, selectedTile, team) ||
		newBuildingType == AUTOCANNON_TURRET || newBuildingType == ROCKET_TURRET)
		buildExample.setColor(whiteTransparent);
	else
		buildExample.setColor(darkRedTransparent);

	buildExample.setPosition(mouseMapCoord);
	window.draw(buildExample);
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
			buildExample.setRotation(270);
		}
		else if (direction == 'a')
		{
			direction = 's';
			buildExample.setRotation(180);
		}
		else if (direction == 's')
		{
			direction = 'd';
			buildExample.setRotation(90);
		}
		else if (direction == 'd')
		{
			direction = 'w';
			buildExample.setRotation(0);
		}
		break;

	default:
		direction = 'w';
		buildExample.setRotation(0);
		break;
	}
}


void BuildingPanel::selectBuildingType(const sf::Vector2i& mouseCoord)
{
	if (remove.press(mouseCoord))
	{
		newBuildingType = REMOVE;
		buildExample.setTextureRect(t1::bc::buildingsInfoTable[newBuildingType].icoRect);
		isBuildingTypeSelected = true;
		oldBuildingType = REMOVE;
		return;
	}

	for (auto& btn : buttons)
	{
		if (btn.second.press(mouseCoord))
			selectedPage = btn.first;
	}

	for (auto& ico : pages[selectedPage])
	{
		if (ico.second.press(mouseCoord))
		{
			newBuildingType = ico.first;
			if (oldBuildingType != newBuildingType)
			{
				buildExample.setTextureRect(t1::bc::buildingsInfoTable[newBuildingType].icoRect);
				isBuildingTypeSelected = true;
				oldBuildingType = newBuildingType;
			}
			else
			{
				isBuildingTypeSelected = false;
				oldBuildingType = VOID_;
			}
			return;
		}
	}
}


void BuildingPanel::placeBuilding(const sf::Vector2f& mouseMapCoord, Team* const team)
{
	std::cout << "building_place_works: " << newBuildingType << '\n';
	TileCoord selectedTile = t1::be::tile(mouseMapCoord.x, mouseMapCoord.y);

	std::lock_guard<std::mutex> guard(t1::system::mt::buildings);
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
}
