
#include "camera.h"
#include "map_structures/pre-settings/pre-settings.h"


Camera::Camera()
{
	size = sf::Vector2i(1024, 720);
	center = size / 2;

	mapScale = 1;

	isMooving = false;
	isScaling = false;

	startTile = { 0, 0 };
	endTile = { 50, 50 };

	mapSize = PreSettings::getMapSize();
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

	camera.setSize(sf::Vector2f(size.x * mapScale / 4, size.y * mapScale / 4));
}


void Camera::resize(sf::RenderWindow& window)
{
	if (size.x != window.getSize().x || size.y != window.getSize().y)	// mainWindow_scaling block
	{
		size.x = window.getSize().x;
		size.y = window.getSize().y;

		camera.setSize(sf::Vector2f(size.x * mapScale, size.y * mapScale));
		window.setView(camera);
	}
}


void Camera::updateMapRegion(sf::RenderWindow& window)
{
	using namespace t1::be;

	sf::Vector2f startPixel = window.mapPixelToCoords(sf::Vector2i(0, 0));
	startTile = { tile(startPixel.x) - 6, tile(startPixel.y) - 6 }; // 6_is_max_building_line_size needed_to_correct_big_buildings_drawing

	sf::Vector2f endPixel = window.mapPixelToCoords(sf::Vector2i(window.getSize().x, window.getSize().y));
	endTile = { tile(endPixel.x) + 1, tile(endPixel.y) + 1 };

	if (startTile.x < 0)
		startTile.x = 0;
	if (startTile.y < 0)
		startTile.y = 0;

	if (endTile.x > mapSize.x)
		endTile.x = mapSize.x;
	if (endTile.y > mapSize.y)
		endTile.y = mapSize.y;
}
