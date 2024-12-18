#pragma once
#ifndef INVENTORY_PANEL_H
#define INVENTORY_PANEL_H

#include <map>
#include "game_interface/ui_window/ui_window/ui_plate.h"
#include "game_interface/ui_window/elements/res_info/res_info.h"

class Team;
class World;

class InventoryWindow : public UIPlate
{
private:
	std::map<int, ResInfo> resInfo;
	World* world;

	InventoryWindow(const InventoryWindow&) = delete;
	InventoryWindow& operator=(const InventoryWindow&) = delete;

public:
	InventoryWindow(World* world);
	~InventoryWindow() = default;

	void interact(const sf::Vector2f& mouseMapCoord, Team* const team);
	void relocateToCoursor();

	void prepareInterfaceSprites() override final;
	void draw(sf::RenderWindow& window) override final;

};

#endif // INVENTORY_PANEL_H
