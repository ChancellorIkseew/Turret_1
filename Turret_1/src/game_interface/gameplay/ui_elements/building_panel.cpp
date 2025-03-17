
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
using Info = BuildingsInfoTable;
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

	const int line1 = 240;
	const int line2 = 282;
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



void BuildingPanel::interact(Team* team, BuildingsMap& buildingsMap, BlueprintsMap& blueprintsMap, const GameMode gameMode, const Gameplay& gameplay)
{
	if (InputHandler::active(t1::BindName::Build) && buildingType != BuildingType::VOID_ && gameplay.noSubWindowSelected())
		placeBuilding(team, buildingsMap, blueprintsMap, gameMode);

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
		for (auto& [type, ico] : page)
			ico.relocateWithOwner(position);

	expensesPanel->relocate(windowSize);
	specificationPanel->relocate(windowSize);
}

bool BuildingPanel::containsCoursor() const
{
	return UIPlate::containsCoursor() ||expensesPanel->containsCoursor();
}

void BuildingPanel::draw(sf::RenderWindow& window)
{
	expensesPanel->setVisible(buildingType != BuildingType::VOID_);
	expensesPanel->interact(buildingType, buildingsPre);
	expensesPanel->draw(window);
	specificationPanel->setVisible(isInfoOpen && buildingType != BuildingType::VOID_);
	specificationPanel->interact(buildingType, buildingsPre);
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
	if (buildingType == BuildingType::VOID_)
		return;
	if (buildingType != BuildingType::STANDARD_CONVEYER && buildingType != BuildingType::SHIELDED_CONVEYER &&
		buildingType != BuildingType::BRIDGE && buildingType != BuildingType::SORTER)
	{
		direction = 'w';
		buildExample.setRotation(0_deg);
	}
	const sf::Vector2f mouseMapCoord = InputHandler::getMouseMapCoord();
	TileCoord selectedTile = t1::be::tile(mouseMapCoord.x, mouseMapCoord.y);
	if (buildingsMap.isAvaluablePlaceBuilding(buildingType, selectedTile, team) ||
		buildingType == BuildingType::AUTOCANNON_TURRET || buildingType == BuildingType::ROCKET_TURRET)
		buildExample.setColor(whiteTransparent);
	else
		buildExample.setColor(darkRedTransparent);

	buildExample.setPosition(mouseMapCoord);
	window.draw(buildExample);
}



void BuildingPanel::rotateBuilding()
{
	switch (buildingType)
	{
	case BuildingType::STANDARD_CONVEYER:
	case BuildingType::SHIELDED_CONVEYER:
	case BuildingType::BRIDGE:
	case BuildingType::SORTER:
		switch (direction)
		{
		case 'w': 
			direction = 'a';
			buildExample.setRotation(270_deg);
			break;
		case 'a':
			direction = 's';
			buildExample.setRotation(180_deg);
			break;
		case 's':
			direction = 'd';
			buildExample.setRotation(90_deg);
			break;
		case 'd':
			direction = 'w';
			buildExample.setRotation(0_deg);
			break;
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
	BuildingType type = ico.getBuildingType();
	if (type == buildingType || InputHandler::active(t1::BindName::Escape))
	{
		buildingType = BuildingType::VOID_;
		isInfoOpen = false;
		return;
	}
	buildingType = type;
	buildExample.setTextureRect(Info::at(buildingType).icoRect);
}


void BuildingPanel::placeBuilding(Team* team, BuildingsMap& buildingsMap, BlueprintsMap& blueprintsMap, const GameMode gameMode) const
{
	std::cout << "building_place_works: " << static_cast<uint16_t>(buildingType) << '\n';
	const sf::Vector2f mouseMapCoord = InputHandler::getMouseMapCoord();
	const TileCoord selectedTile = t1::be::tile(mouseMapCoord.x, mouseMapCoord.y);

	std::lock_guard<std::mutex> guard(t1::system::mt::buildings);
	if (gameMode != GameMode::SANDBOX)
	{
		blueprintsMap.placeBlueprint(buildingsMap, buildingType, direction, selectedTile);
		return;
	}

	if (buildingType == BuildingType::REMOVE)
		buildingsMap.demolishBuilding(selectedTile);
	else
		buildingsMap.constructBuilding(buildingType, direction, selectedTile, team);	
}


void BuildingPanel::pickBuildingType(const BuildingsMap& buildingsMap, const BlueprintsMap& blueprint)
{
	const sf::Vector2f mouseMapCoord = InputHandler::getMouseMapCoord();
	const TileCoord selectedTile = t1::be::tile(mouseMapCoord.x, mouseMapCoord.y);
	BuildingType type = blueprint.getType(selectedTile);
	if (type == BuildingType::VOID_)
		type = buildingsMap.getBuildingType(selectedTile);
	buildingType = type;
	buildExample.setTextureRect(Info::at(buildingType).icoRect);
}
