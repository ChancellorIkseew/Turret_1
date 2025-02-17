#pragma once
#ifndef EXPENSES_PANEL_H
#define EXPENSES_PANEL_H

#include <map>

#include "game_interface/ui_window/ui_window/ui_window.h"
#include "game_interface/ui_window/elements/res_info/res_info.h"
#include "map_structures/buildings/building/buildings_info.h"
#include "map_structures/buildings/building/buildings_enum.h"


class ExpensesPanel : public UIWindow
{
private:
	static BuildingInfo nullInfo;
	BuildingInfo& buildingInfo = nullInfo;
	
	sf::Text title;
	std::map<int, ResInfo> resInfo;

	ExpensesPanel(const ExpensesPanel&) = delete;
	ExpensesPanel& operator=(const ExpensesPanel&) = delete;
	
public:
	ExpensesPanel();
	~ExpensesPanel() = default;
	
	void interact(const BuildingType index);
	void relocate(const sf::Vector2u windowSize) override final;

	void prepareInterfaceSprites() override final;
	void draw(sf::RenderWindow& window) override final;
	
};

#endif // EXPENSES_PANEL_H
