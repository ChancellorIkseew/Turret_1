
#include <iostream>

#include "building_panel.h"
#include "building_panel/buildings_pages.h"

#include "game_interface/gameplay/gameplay.h"
#include "game_interface/ui_window/sub_win_util/fonts.h"

#include "map_structures/terrain/terrain.h"
#include "map_structures/blueprints/blueprints_map.h"
#include "map_structures/buildings/buildings_map/buildings_map.h"
#include "map_structures/buildings/building/buildings_enum.h"
#include "map_structures/base_engine/base_engine.h"

#include "t1_system/input/input_handler.h"
#include "t1_system/t1_mutex.h"
#include "t1_system/sleep.h"

using namespace sf::Literals;
constexpr float _F_HALF_TILE_ = static_cast<float>(_HALF_TILE_);
constexpr sf::Vector2f BLUEPRINT_ORIGIN = sf::Vector2f(_F_HALF_TILE_, _F_HALF_TILE_);

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


BuildingPanel::BuildingPanel() : UIWindow(sf::Vector2i(324, 192))
{
	selectedPage = LOGISTICS;
	isBuildingTypeSelected = false;
	newBuildingType = BuildingType::VOID_;
	oldBuildingType = BuildingType::VOID_;
	direction = 'w';
	isInfoOpen = false;

	this->prepareInterfaceSprites();
	expensesPanel = std::make_unique<ExpensesPanel>();
	specificationPanel = std::make_unique<SpecificationPanel>();
}


void BuildingPanel::prepareInterfaceSprites()
{
	buildingsImage.loadFromFile("images/buildings_ico.bmp"); //Building_example_on_coursor
	buildingsImage.createMaskFromColor(sf::Color(0, 255, 0));
	buildingsTexture.loadFromImage(buildingsImage);
	buildExample.setOrigin(BLUEPRINT_ORIGIN);

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

	for (auto& [name, page] : pages)
		t1::bc::arrangePage(page);

	t1::bc::initUtil(pages[UTIL]);
}



void BuildingPanel::interact(Team* team, BuildingsMap& buildingsMap, BlueprintsMap& blueprintsMap, const Gameplay& gameplay)
{
	if (InputHandler::active(t1::BindName::Build) && isBuildingTypeSelected && gameplay.noSubWindowSelected())
		placeBuilding(team, buildingsMap, blueprintsMap);

	if (InputHandler::jactive(t1::BindName::Rotate_building) || InputHandler::jactive(t1::BindName::RMB))
		rotateBuilding();

	if (InputHandler::jactive(t1::BindName::Pipette) && gameplay.noSubWindowSelected())
		pickBuildingType(buildingsMap, blueprintsMap);
	////
	if (info.press())
		isInfoOpen = !isInfoOpen;
	
	for (auto& btn : buttons)
		if (btn.second.press())
			selectedPage = btn.first;

	for (auto& ico : pages[selectedPage])
		selectBuildingType(ico.second);
	for (auto& ico : pages[UTIL])
		selectBuildingType(ico.second);
}



void BuildingPanel::relocate(const sf::Vector2i windowSize)
{
	position = windowSize - size;
	info.relocateWithOwner(position);

	for (auto& [name, button] : buttons)
		button.relocateWithOwner(position);

	for (auto& [pageName, page] : pages)
	{
		for (auto& [type, ico] : page)
			ico.relocateWithOwner(position);
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
	expensesPanel->setVisible(isBuildingTypeSelected);
	expensesPanel->interact(newBuildingType, buildingsPre);
	expensesPanel->draw(window);
	specificationPanel->setVisible(isInfoOpen && isBuildingTypeSelected);
	specificationPanel->interact(newBuildingType, buildingsPre);
	specificationPanel->draw(window);
	drawBase(window);
	info.draw(window);
	for (auto& [name, button] : buttons)
		button.draw(window);
	for (auto& [type, ico] : pages[selectedPage])
		ico.draw(window);
	for (auto& [type, ico] : pages[UTIL])
		ico.draw(window);
}



void BuildingPanel::drawBuildExample(sf::RenderWindow& window, Team* team, const BuildingsMap& buildingsMap)
{
	const sf::Vector2f mouseMapCoord = InputHandler::getMouseMapCoord();

	if (!isBuildingTypeSelected)
		return;
	if (newBuildingType != BuildingType::STANDARD_CONVEYER && newBuildingType != BuildingType::SHIELDED_CONVEYER &&
		newBuildingType != BuildingType::BRIDGE && newBuildingType != BuildingType::SORTER)
	{
		direction = 'w';
		buildExample.setRotation(0_deg);
	}

	TileCoord selectedTile = t1::be::tile(mouseMapCoord.x, mouseMapCoord.y);
	if (buildingsMap.isAvaluablePlaceBuilding(newBuildingType, selectedTile, team) ||
		newBuildingType == BuildingType::AUTOCANNON_TURRET || newBuildingType == BuildingType::ROCKET_TURRET)
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
	case BuildingType::STANDARD_CONVEYER:
	case BuildingType::SHIELDED_CONVEYER:
	case BuildingType::BRIDGE:
	case BuildingType::SORTER:
		if (direction == 'w')
		{
			direction = 'a';
			buildExample.setRotation(270_deg);
		}
		else if (direction == 'a')
		{
			direction = 's';
			buildExample.setRotation(180_deg);
		}
		else if (direction == 's')
		{
			direction = 'd';
			buildExample.setRotation(90_deg);
		}
		else if (direction == 'd')
		{
			direction = 'w';
			buildExample.setRotation(0_deg);
		}
		break;

	default:
		direction = 'w';
		buildExample.setRotation(0_deg);
		break;
	}
}


void BuildingPanel::selectBuildingType(BuildingIco& ico)
{
	if (!ico.press() && !InputHandler::active(t1::BindName::Escape))
		return;
	newBuildingType = ico.getBuildingType();
	if (oldBuildingType == newBuildingType || InputHandler::active(t1::BindName::Escape))
	{
		isBuildingTypeSelected = false;
		oldBuildingType = BuildingType::VOID_;
		isInfoOpen = false;
		return;
	}
	buildExample.setTextureRect(t1::bc::buildingsInfoTable[newBuildingType].icoRect);
	isBuildingTypeSelected = true;
	oldBuildingType = newBuildingType;
}


void BuildingPanel::placeBuilding(Team* team, BuildingsMap& buildingsMap, BlueprintsMap& blueprintsMap) const
{
	std::cout << "building_place_works: " << static_cast<uint16_t>(newBuildingType) << '\n';
	const sf::Vector2f mouseMapCoord = InputHandler::getMouseMapCoord();
	const TileCoord selectedTile = t1::be::tile(mouseMapCoord.x, mouseMapCoord.y);

	std::lock_guard<std::mutex> guard(t1::system::mt::buildings);
	if (newBuildingType == BuildingType::REMOVE)
	{
		if (buildingsMap.isTurretOnTile(selectedTile))
			buildingsMap.removeTurret(selectedTile);
		else
			buildingsMap.demolishBuilding(selectedTile);
	}
	else if (newBuildingType == BuildingType::AUTOCANNON_TURRET || newBuildingType == BuildingType::ROCKET_TURRET)
	{
		if (!buildingsMap.isTurretOnTile(selectedTile))
			buildingsMap.setTurret(newBuildingType, selectedTile, team);
	}
	else
	{
		//buildingsMap.constructBuilding(newBuildingType, direction, selectedTile, team);
		blueprintsMap.placeBlueprint(newBuildingType, direction, selectedTile);
	}
}


void BuildingPanel::pickBuildingType(const BuildingsMap& buildingsMap, const BlueprintsMap& blueprint)
{
	const sf::Vector2f mouseMapCoord = InputHandler::getMouseMapCoord();
	const TileCoord selectedTile = t1::be::tile(mouseMapCoord.x, mouseMapCoord.y);
	BuildingType type = blueprint.getType(selectedTile);
	if (type == BuildingType::VOID_)
		type = buildingsMap.getBuildingType(selectedTile);
	newBuildingType = type;
	isBuildingTypeSelected = type != BuildingType::VOID_;
	buildExample.setTextureRect(t1::bc::buildingsInfoTable[newBuildingType].icoRect);
}
