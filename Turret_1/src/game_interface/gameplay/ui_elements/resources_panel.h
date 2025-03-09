#pragma once
#ifndef RESOURCES_PANEL_H
#define RESOURCES_PANEL_H

#include <mutex>
#include <map>
#include "game_interface/ui_window/ui_window/ui_window.h"
#include "game_interface/ui_window/elements/res_info/res_info.h"
#include "map_structures/resources/res_enum.h"

class Team;

class ResourcesPanel : public UIWindow
{
private:
	static inline std::mutex mutex;
	std::map<ResType, ResInfo> resInfo;

	ResourcesPanel(const ResourcesPanel&) = delete;
	ResourcesPanel& operator=(const ResourcesPanel&) = delete;
	
public:
	ResourcesPanel();
	~ResourcesPanel() = default;
	
	void interact(Team& team);
	void relocate(const sf::Vector2i windowSizeY) override final;
	
	void prepareInterfaceSprites() override final;
	void draw(sf::RenderWindow &window) override final;
	
};

#endif // RESOURCES_PANEL_H
