#pragma once
#ifndef BUILDING_PANEL_H
#define BUILDING_PANEL_H

#include <SFML\Graphics.hpp>

#include "sub_windows_util/sub_window.h"


class BuildingPanel : public SubWindow
{
private:	
	
	sf::Image buildingsImage;
	sf::Texture buildingsTexture;

	sf::Sprite buildExampleSprite;
	
	sf::Sprite towerButtonSprite;
	sf::Sprite wallButtonSprite;
	sf::Sprite smallDrillButtonSprite;
	sf::Sprite bigDrillButtonSprite;
	sf::Sprite shellFactoryButtonSprite;
	sf::Sprite rocketFactoryButtonSprite;
	sf::Sprite allocationNodeButtonSprite;
	sf::Sprite generatorButtonSprite;
	sf::Sprite turretButtonSprite;
	sf::Sprite rocketTurretButtonSprite;
	sf::Sprite removeBuildingButtonSprite;
	sf::Sprite conveyerButtonSprite;
	sf::Sprite shieldedConveyerButtonSprite;
	sf::Sprite intersectionButtonSprite;
	sf::Sprite routerButtonSprite;
	sf::Sprite sorterButtonSprite;

	sf::Vector2i mouseCoord;
	bool isBuildingTypeSelected;
	int buildingType;
	char direction;

	void selectBuildingType(bool& isBuildingTypeSelected);

	void selectBuildingTexture(int buildingType);

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
	
	void interact(const sf::Vector2i& mouseCoord, const sf::Vector2f& mouseMapCoord);
	void rotateBuilding();
	void relocate(int windowSizeX, int windowSizeY) override final;
	
	void prepareInterfaceSprites() override final;
	void draw(sf::RenderWindow& window) override final;
	void drawBuildExample(sf::RenderWindow& window, const sf::Vector2f& mouseMapCoord);
	
};

#endif // BUILDING_PANEL_H
