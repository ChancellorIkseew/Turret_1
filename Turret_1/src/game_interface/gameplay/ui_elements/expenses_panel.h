#pragma once
#ifndef EXPENSES_PANEL_H
#define EXPENSES_PANEL_H

#include <map>

#include "game_interface/ui_window/ui_window/ui_window.h"
#include "game_interface/ui_window/elements/res_info/res_info.h"
#include "map_structures/buildings/building/buildings_info.h"
#include "map_structures/buildings/building/buildings_enum.h"
#include "map_structures/pre-settings/pre_settings/buildings_pre.h"


class ExpensesPanel : public UIWindow
{
private:
	static BuildingInfo nullInfo;
	BuildingInfo& buildingInfo = nullInfo;
	
	sf::Text title = sf::Text(turretClassic);
	std::map<ResType, ResInfo> resInfo;

	ExpensesPanel(const ExpensesPanel&) = delete;
	ExpensesPanel& operator=(const ExpensesPanel&) = delete;
	void prepareInterfaceSprites() override final;
	
public:
	ExpensesPanel();
	~ExpensesPanel() = default;
	
	void interact(const BuildingType index, const BuildingsPre& buildingsPre);
	void relocate(const sf::Vector2i windowSize) override final;

	void draw(sf::RenderWindow& window) override final;
	
};

#endif // EXPENSES_PANEL_H
