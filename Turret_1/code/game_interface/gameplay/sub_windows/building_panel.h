#pragma once
#ifndef BUILDING_PANEL_H
#define BUILDING_PANEL_H

#include <map>
#include <SFML\Graphics.hpp>

#include "sub_windows_util/sub_window.h"

class Team;

class BuildingPanel : public SubWindow
{
private:	
	
	static inline sf::Image buildingsImage;
	static inline sf::Texture buildingsTexture;
	static inline sf::Sprite buildExampleSprite;

	bool isBuildingTypeSelected;
	int oldBuildingType, newBuildingType;
	char direction;

	BuildingPanel();
	BuildingPanel(const BuildingPanel&) = delete;
	BuildingPanel& operator=(const BuildingPanel&) = delete;
	~BuildingPanel() = default;
	
public:
	
	static BuildingPanel& getInstance()
	{
		static BuildingPanel self;
		return self;
	}
	
	void interact(const sf::Vector2i& mouseCoord, const sf::Vector2f& mouseMapCoord, Team* team);
	void rotateBuilding();
	void relocate(const sf::Vector2u windowSize) override final;
	
	void prepareInterfaceSprites() override final;
	void draw(sf::RenderWindow& window) override final;
	void drawBuildExample(sf::RenderWindow& window, const sf::Vector2f& mouseMapCoord);
	
};

#endif // BUILDING_PANEL_H
