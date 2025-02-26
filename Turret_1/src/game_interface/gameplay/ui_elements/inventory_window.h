#pragma once
#ifndef INVENTORY_PANEL_H
#define INVENTORY_PANEL_H

#include <map>
#include "game_interface/ui_window/ui_window/ui_plate.h"
#include "game_interface/ui_window/elements/res_info/res_info.h"
#include "map_structures/base_engine/base_engine.h"

class Team;
class BuildingsMap;

class InventoryWindow : public UIPlate
{
private:
	std::map<ResType, ResInfo> resInfo;
	TileCoord targetedTile;

	InventoryWindow(const InventoryWindow&) = delete;
	InventoryWindow& operator=(const InventoryWindow&) = delete;

public:
	InventoryWindow();
	~InventoryWindow() = default;

	void interact(Team* team, const BuildingsMap& buildingsMap);
	void relocateToCoursor();

	void prepareInterfaceSprites() override final { /* No additional interface. */ }
	void draw(sf::RenderWindow& window) override final;

};

#endif // INVENTORY_PANEL_H
