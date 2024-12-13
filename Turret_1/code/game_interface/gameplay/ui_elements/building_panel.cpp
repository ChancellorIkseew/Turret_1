
#include <iostream>

#include "building_panel.h"
#include "building_panel/buildings_pages.h"

#include "game_interface/gameplay/gameplay.h"
#include "game_interface/ui_window/sub_win_util/fonts.h"

#include "map_structures/terrain/terrain.h"
#include "map_structures/buildings/buildings_map/buildings_map.h"
#include "map_structures/buildings/building/buildings_enum.h"
#include "map_structures/base_engine/base_engine.h"

#include "t1_system/input/input_handler.h"
#include "t1_system/t1_mutex.h"
#include "t1_system/sleep.h"

enum Pages
{
	UTIL = 0,
	LOGISTICS = 1,
	DRILLS = 2,
	FACTORIES = 3,
	ELECTRICS = 4,
	WALLS = 5,
	TURRETS = 6,
	SPECIAL = 7,
	STORAGES = 8,
};


BuildingPanel::BuildingPanel() : UIWindow(sf::Vector2u(324, 192), sf::Vector2u(0, 0))
{
	selectedPage = LOGISTICS;
	isBuildingTypeSelected = false;
	newBuildingType = VOID_;
	oldBuildingType = VOID_;
	direction = 'w';
	isInfoOpen = false;

	this->prepareInterfaceSprites();
	expensesPanel = std::make_unique<ExpensesPanel>();
	specificationPanel = std::make_unique<SpecificationPanel>();
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
	info = Button("building/info_ico.bmp", sf::Vector2i(32, 32), sf::Vector2i(10, 10));

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

	t1::bc::initUtil(pages[UTIL]);
}



void BuildingPanel::interact(const sf::Vector2f& mouseMapCoord, Team* const team)
{
	if (InputHandler::active(t1::KeyName::Build) && isBuildingTypeSelected && (*Gameplay::getInstance()).noSubWindowSelected())
	{
		placeBuilding(mouseMapCoord, team);
		t1::system::sleep(150);
		return;
	}

	if (InputHandler::jactive(t1::KeyName::Rotate_building))
	{
		rotateBuilding();
		t1::system::sleep(150);
		return;
	}

	if (info.press())
		isInfoOpen = !isInfoOpen;
	
	for (auto& btn : buttons)
	{
		if (btn.second.press())
			selectedPage = btn.first;
	}

	for (auto& ico : pages[selectedPage])
		selectBuildingType(ico.second);
	for (auto& ico : pages[UTIL])
		selectBuildingType(ico.second);
}



void BuildingPanel::relocate(const sf::Vector2u windowSize)
{
	position = windowSize - size;
	info.relocateWithOwner(position);

	for (auto& btn : buttons)
		btn.second.relocateWithOwner(position);

	for (auto& pg : pages)
	{
		for (auto& ico : pg.second)
			ico.second.relocateWithOwner(position);
	}

	expensesPanel->relocate(windowSize);
	specificationPanel->relocate(windowSize);
}

bool BuildingPanel::containsCoursor() const
{
	return 
		UIPlate::containsCoursor() ||
		expensesPanel->containsCoursor();
}

void BuildingPanel::draw(sf::RenderWindow& window)
{
	if (isBuildingTypeSelected)
	{
		expensesPanel->interact(newBuildingType);
		expensesPanel->draw(window);
		if (isInfoOpen)
		{
			specificationPanel->interact(newBuildingType);
			specificationPanel->draw(window);
		}	
	}
	drawBase(window);
	info.draw(window);
	for (auto& btn : buttons)
		btn.second.draw(window);
	for (auto& ico : pages[selectedPage])
		ico.second.draw(window);
	for (auto& ico : pages[UTIL])
		ico.second.draw(window);
}



void BuildingPanel::drawBuildExample(sf::RenderWindow& window, Team* const team)
{
	const sf::Vector2f mouseMapCoord = InputHandler::getMouseMapCoord();

	if (!isBuildingTypeSelected)
		return;
	if (newBuildingType != STANDARD_CONVEYER && newBuildingType != SHIELDED_CONVEYER &&
		newBuildingType != BRIDGE && newBuildingType != SORTER)
	{
		direction = 'w';
		buildExample.setRotation(0.0f);
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


void BuildingPanel::selectBuildingType(BuildingIco& ico)
{
	if (!ico.press())
		return;
	newBuildingType = ico.getBuildingType();
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
		isInfoOpen = false;
	}
}


void BuildingPanel::placeBuilding(const sf::Vector2f& mouseMapCoord, Team* const team)
{
	std::cout << "building_place_works: " << newBuildingType << '\n';
	const TileCoord selectedTile = t1::be::tile(mouseMapCoord.x, mouseMapCoord.y);

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
