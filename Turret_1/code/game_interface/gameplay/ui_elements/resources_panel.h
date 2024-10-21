#pragma once
#ifndef RESOURCES_PANEL_H
#define RESOURCES_PANEL_H

#include <mutex>
#include <map>
#include "game_interface/ui_window/ui_window/ui_window.h"
#include "game_interface/ui_window/elements/res_info/res_info.h"

class Team;

class ResourcesPanel : public UIWindow
{
private:
	static inline std::mutex mutex;
	std::map<int, ResInfo> resInfo;

	ResourcesPanel();
	ResourcesPanel(const ResourcesPanel&) = delete;
	ResourcesPanel& operator=(const ResourcesPanel&) = delete;
	~ResourcesPanel() = default;
	
public:
	
	static ResourcesPanel& getInstance()
	{
		static ResourcesPanel self;
		return self;
	}
	
	void interact(Team& team);
	void relocate(const sf::Vector2u windowSizeY) override final;
	
	void prepareInterfaceSprites() override final;
	void draw(sf::RenderWindow &window) override final;
	
};

#endif // RESOURCES_PANEL_H
