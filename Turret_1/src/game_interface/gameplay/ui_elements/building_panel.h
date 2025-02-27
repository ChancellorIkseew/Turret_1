#pragma once
#ifndef BUILDING_PANEL_H
#define BUILDING_PANEL_H

#include <map>
#include "game_interface/ui_window/ui_window/ui_window.h"
#include "game_interface/ui_window/elements/button/button.h"
#include "game_interface/ui_window/elements/button/building_ico.h"
#include "expenses_panel.h"
#include "specification_panel.h"
#include "map_structures/pre-settings/pre_settings/buildings_pre.h"

enum class BuildingType : uint16_t;

class Team;
class World;
class BuildingsMap;
class Gameplay;

class BuildingPanel : public UIWindow
{
private:
	Button info;
	std::map<int, Button> buttons;
	std::map<int, std::map<BuildingType, BuildingIco>> pages;
	
	static inline sf::Image buildingsImage;
	static inline sf::Texture buildingsTexture;
	static inline sf::Sprite buildExample;

	int selectedPage;
	bool isBuildingTypeSelected;
	BuildingType oldBuildingType, newBuildingType;
	char direction;
	bool isInfoOpen;
	BuildingsPre buildingsPre;

	inline void selectBuildingType(BuildingIco& ico);
	inline void rotateBuilding();
	inline void placeBuilding(const sf::Vector2f& mouseMapCoord, Team* team, BuildingsMap& buildingsMap) const;

	std::unique_ptr<ExpensesPanel> expensesPanel;
	std::unique_ptr<SpecificationPanel> specificationPanel;

	BuildingPanel(const BuildingPanel&) = delete;
	BuildingPanel& operator=(const BuildingPanel&) = delete;
	
public:
	BuildingPanel();
	~BuildingPanel() = default;
	
	void initPresettings(const BuildingsPre& buildingsPre) { this->buildingsPre = buildingsPre; }
	void interact(const sf::Vector2f& mouseMapCoord, Team* team, BuildingsMap& buildingsMap, const Gameplay& gameplay);
	void relocate(const sf::Vector2u windowSize) override final;
	bool containsCoursor() const override final;
	
	void prepareInterfaceSprites() override final;
	void draw(sf::RenderWindow& window) override final;
	void drawBuildExample(sf::RenderWindow& window, Team* team, const BuildingsMap& buildingsMap);
	
};

#endif // BUILDING_PANEL_H
