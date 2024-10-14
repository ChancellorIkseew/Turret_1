#pragma once
#ifndef SPECIFICATIONS_PANEL_H
#define SPECIFICATIONS_PANEL_H

#include "game_interface/sub_window/sub_window/sub_window.h"
#include "game_interface/sub_window/elements/res_info/res_info.h"
#include "map_structures/buildings/building/buildings_info.h"


class SpecificationsPanel : public SubWindow
{
private:
	static BuildingInfo nullInfo;
	BuildingInfo& buildingInfo = nullInfo;
	
	sf::Text titleText;
	sf::Text durabilityText;
	sf::Text descriptionText;
	
	ResInfo stoneInfo;
	ResInfo ironInfo;
	ResInfo copperInfo;
	ResInfo siliconInfo;
	ResInfo coalInfo;
	ResInfo sulfurInfo;
	ResInfo ACShellsInfo;
	ResInfo rocketInfo;

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
