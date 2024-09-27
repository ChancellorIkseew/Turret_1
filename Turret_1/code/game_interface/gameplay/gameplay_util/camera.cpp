
#include <iostream>

#include "camera.h"
#include "map_structures/pre-settings/pre-settings.h"



Camera::Camera()
{
	sizeX = 1024;
	sizeY = 720;

	centerX = int(sizeX / 2);
	centerY = int(sizeY / 2);

	mapScale = 1;

	isMooving = false;
	isScaling = false;

	startTile = { 0, 0 };
	endTile = { 50, 50 };
}



void Camera::move()
{

}



void Camera::scale(sf::Event event)
{
	if ((event.mouseWheel.delta) == 1)
	{
		if (mapScale >= 2)
		{
			mapScale = mapScale / 1.2f;
		}
	}

	if ((event.mouseWheel.delta) == -1)
	{
		mapScale = mapScale * 1.2f;
	}

	camera.setSize(sf::Vector2f(sizeX * mapScale / 4, sizeY * mapScale / 4));
}



void Camera::resize(sf::RenderWindow& window)
{
	if (sizeX != window.getSize().x || sizeY != window.getSize().y)	// mainWindow_scaling block
	{

		sizeX = window.getSize().x;
		sizeY = window.getSize().y;


		//std::cout << cameraSizeX << " " << cameraSizeY << '\n';
		//mainWindow.setView(overlay);



		camera.setSize(sf::Vector2f(sizeX * mapScale, sizeY * mapScale));
		window.setView(camera);


		//mouseCoord = sf::Mouse::getPosition(mainWindow); 
		
	}
}



void Camera::updateMapRegion(sf::RenderWindow& window)
{
	using namespace t1::be;

	sf::Vector2f startTile = window.mapPixelToCoords(sf::Vector2i(0, 0));
	this->startTile = { tile(startTile.x) - 6, tile(startTile.y) - 6 }; // 6_is_max_building_line_size needed_to_correct_big_buildings_drawing
	std::cout << "startX: " << this->startTile.x << " startY: " << this->startTile.y << '\n';

	sf::Vector2f endTile = window.mapPixelToCoords(sf::Vector2i(window.getSize().x, window.getSize().y));
	this->endTile = { tile(endTile.x) + 1, tile(endTile.y) + 1 };
	std::cout << "endX: " << this->endTile.x << " endY: " << this->endTile.y << '\n';

	if (this->startTile.x < 0)
	{
		this->startTile.x = 0;
	}

	if (this->startTile.y < 0)
	{
		this->startTile.y = 0;
	}


	if (this->endTile.x > PreSettings::getMapMaxX())
	{
		this->endTile.x = PreSettings::getMapMaxX();
	}

	if (this->endTile.y > PreSettings::getMapMaxY())
	{
		this->endTile.y = PreSettings::getMapMaxY();
	}

}


Camera::~Camera()
{

}