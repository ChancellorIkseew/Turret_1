#pragma once
#ifndef SPECIFICATIONS_PANEL_H
#define SPECIFICATIONS_PANEL_H

#include <SFML\Graphics.hpp>

#include "sub_windows_util/sub_window.h"
#include "sub_windows_util/res_info.h"


class SpecificationsPanel : public SubWindow
{
private:
	
	int index;
	
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
	
	void interact(sf::RenderWindow& window, int index);
	void relocate(int windowSizeX, int windowSizeY) override final;

	void prepareInterfaceSprites() override final;
	void draw(sf::RenderWindow& window) override final;
	
};


#endif // SPECIFICATIONS_PANEL_H
