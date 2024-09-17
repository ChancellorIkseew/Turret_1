#pragma once
#ifndef RESOURCES_PANEL_H
#define RESOURCES_PANEL_H

#include <SFML\Graphics.hpp>

#include "sub_windows_util/sub_window.h"
#include "sub_windows_util/res_info.h"


class ResourcesPanel : public SubWindow
{
private:	

	ResInfo stoneInfo;
	ResInfo ironInfo;
	ResInfo copperInfo;
	ResInfo siliconInfo;
	ResInfo coalInfo;
	ResInfo sulfurInfo;
	ResInfo ACShellsInfo;
	ResInfo rocketInfo;
	
public:
	
	ResourcesPanel();
	~ResourcesPanel() = default;
	
	void prepareInterfaceSprites();
	
	void interactResourcesPanel(sf::RenderWindow &window);
	
	void relocate(int windowSizeX, int windowSizeY) override;
	
	void drawResourcesPanel(sf::RenderWindow &window);
	
};


#endif // RESOURCES_PANEL_H
