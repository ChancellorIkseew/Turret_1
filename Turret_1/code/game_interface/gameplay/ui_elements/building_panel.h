#pragma once
#ifndef BUILDING_PANEL_H
#define BUILDING_PANEL_H

#include <map>
#include "game_interface/ui_window/ui_window/ui_window.h"
#include "game_interface/ui_window/elements/button/button.h"
#include "game_interface/ui_window/elements/button/building_ico.h"
#include "expenses_panel.h"
#include "specification_panel.h"

class Team;

class BuildingPanel : public UIWindow
{
private:
	Button info;
	std::map<int, Button> buttons;
	std::map<int, std::map<uint16_t, BuildingIco>> pages;
	
	static inline sf::Image buildingsImage;
	static inline sf::Texture buildingsTexture;
	static inline sf::Sprite buildExample;

	int selectedPage;
	bool isBuildingTypeSelected;
	int oldBuildingType, newBuildingType;
	char direction;
	bool isInfoOpen;

	inline void selectBuildingType(BuildingIco& ico);
	inline void rotateBuilding();
	inline void placeBuilding(const sf::Vector2f& mouseMapCoord, Team* const team);

	std::unique_ptr<ExpensesPanel> expensesPanel;
	std::unique_ptr<SpecificationPanel> specificationPanel;

	BuildingPanel(const BuildingPanel&) = delete;
	BuildingPanel& operator=(const BuildingPanel&) = delete;
	
public:
	BuildingPanel();
	~BuildingPanel() = default;
	
	void interact(const sf::Vector2f& mouseMapCoord, Team* const team);
	void relocate(const sf::Vector2u windowSize) override final;
	bool containsCoursor() const override final;
	
	void prepareInterfaceSprites() override final;
	void draw(sf::RenderWindow& window) override final;
	void drawBuildExample(sf::RenderWindow& window, Team* const team);
	
};

#endif // BUILDING_PANEL_H
