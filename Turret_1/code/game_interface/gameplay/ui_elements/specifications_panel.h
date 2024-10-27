#pragma once
#ifndef SPECIFICATIONS_PANEL_H
#define SPECIFICATIONS_PANEL_H

#include <map>

#include "game_interface/ui_window/ui_window/ui_window.h"
#include "game_interface/ui_window/elements/res_info/res_info.h"
#include "map_structures/buildings/building/buildings_info.h"


class SpecificationsPanel : public UIWindow
{
private:
	static BuildingInfo nullInfo;
	BuildingInfo& buildingInfo = nullInfo;
	
	sf::Text title;
	sf::Text durability;
	sf::Text description;
	
	std::map<int, ResInfo> resInfo;

	SpecificationsPanel(const SpecificationsPanel&) = delete;
	SpecificationsPanel& operator=(const SpecificationsPanel&) = delete;
	
public:
	SpecificationsPanel();
	~SpecificationsPanel() = default;
	
	void interact(const int index);
	void relocate(const sf::Vector2u windowSize) override final;

	void prepareInterfaceSprites() override final;
	void draw(sf::RenderWindow& window) override final;
	
};

#endif // SPECIFICATIONS_PANEL_H
