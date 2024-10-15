#pragma once
#ifndef SPECIFICATIONS_PANEL_H
#define SPECIFICATIONS_PANEL_H

#include <map>

#include "game_interface/sub_window/sub_window/sub_window.h"
#include "game_interface/sub_window/elements/res_info/res_info.h"
#include "map_structures/buildings/building/buildings_info.h"


class SpecificationsPanel : public SubWindow
{
private:
	static BuildingInfo nullInfo;
	BuildingInfo& buildingInfo = nullInfo;
	
	sf::Text title;
	sf::Text durability;
	sf::Text description;
	
	std::map<int, ResInfo> resInfo;

	SpecificationsPanel();
	SpecificationsPanel(const SpecificationsPanel&) = delete;
	SpecificationsPanel& operator=(const SpecificationsPanel&) = delete;
	~SpecificationsPanel() = default;
	
public:

	static SpecificationsPanel& getInstance()
	{
		static SpecificationsPanel self;
		return self;
	}
	
	void interact(const int index);

	void prepareInterfaceSprites() override final;
	void draw(sf::RenderWindow& window) override final;
	
};

#endif // SPECIFICATIONS_PANEL_H
