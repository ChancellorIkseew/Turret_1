#pragma once
#ifndef RESOURCES_PANEL_H
#define RESOURCES_PANEL_H

#include <SFML\Graphics.hpp>
#include <mutex>

#include "sub_windows_util/sub_window.h"
#include "sub_windows_util/res_info.h"

class Team;

class ResourcesPanel : public SubWindow
{
private:
	static inline std::mutex mutex;

	ResInfo stoneInfo;
	ResInfo ironInfo;
	ResInfo copperInfo;
	ResInfo siliconInfo;
	ResInfo coalInfo;
	ResInfo sulfurInfo;
	ResInfo ACShellsInfo;
	ResInfo rocketInfo;

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
	void relocate(int windowSizeX, int windowSizeY) override final;
	
	void prepareInterfaceSprites() override final;
	void draw(sf::RenderWindow &window) override final;
	
};


#endif // RESOURCES_PANEL_H
