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

	static inline SpecificationsPanel* _self = 0;
	SpecificationsPanel();
	SpecificationsPanel(const SpecificationsPanel&) = delete;
	SpecificationsPanel& operator=(const SpecificationsPanel&) = delete;
	~SpecificationsPanel() = default;
	
public:

	static SpecificationsPanel* getInstance()
	{
		if (!_self)
		{
			_self = new SpecificationsPanel();
		}
		return _self;
	}

	static bool deleteInstance()
	{
		if (_self)
		{
			delete _self;
			_self = 0;
			return true;
		}
		return false;
	}
	
	void interact(sf::RenderWindow& window, int index);
	void relocate(int windowSizeX, int windowSizeY) override;

	void prepareInterfaceSprites() override;
	void draw(sf::RenderWindow& window) override;
	
};


#endif // SPECIFICATIONS_PANEL_H