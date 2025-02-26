#pragma once
#ifndef SPECIFICATION_PANEL_H
#define SPECIFICATION_PANEL_H

#include <map>

#include "game_interface/ui_window/ui_window/ui_window.h"
#include "game_interface/ui_window/elements/res_info/res_info.h"
#include "map_structures/buildings/building/buildings_info.h"
#include "map_structures/buildings/building/buildings_enum.h"
#include "map_structures/pre-settings/pre-settings.h"


class SpecificationPanel : public UIWindow
{
private:
	static BuildingInfo nullInfo;
	BuildingInfo& buildingInfo = nullInfo;

	sf::Text title;
	sf::Text durability;
	sf::Text description;

	std::map<ResType, ResInfo> resInfo;

	SpecificationPanel(const SpecificationPanel&) = delete;
	SpecificationPanel& operator=(const SpecificationPanel&) = delete;

public:
	SpecificationPanel();
	~SpecificationPanel() = default;

	void interact(const BuildingType index, const BuildingsPre& buildingsPre);
	void relocate(const sf::Vector2u windowSize) override final;

	void prepareInterfaceSprites() override final;
	void draw(sf::RenderWindow& window) override final;
	bool getIsVisible();

};

#endif // SPECIFICATION_PANEL_H
