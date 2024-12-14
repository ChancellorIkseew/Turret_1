
#include "camera.h"
#include "map_structures/pre-settings/pre-settings.h"
#include "t1_system/input/input_handler.h"
#include <iostream>

constexpr float MIN_MAP_SCALE = 0.5f, MAX_MAP_SCALE = 5.0f;
constexpr float SCALE_FACTOR = 1.2f;
constexpr float MOTION_SPEED_MODIFIER = 20.0f;
constexpr int MAX_MAP_STRUCTURE_SIZE = 6;

Camera::Camera()
{
	windowSize = sf::Vector2f(1024, 720);

	mapScale = MIN_MAP_SCALE;

	startTile = TileCoord(0, 0);
	endTile = TileCoord(0, 0);

	tileMapSize = PreSettings::getTerrain().mapSize;
	pixelMapSize = t1::be::pixel(tileMapSize);
}


void Camera::interact(const sf::RenderWindow& window)
{
	resize(window);
	scale();
	moveByMouse();
	moveByWASD();
	avoidEscapeFromMap();
	updateMapRegion(window);
}


void Camera::moveByMouse()
{
	if (InputHandler::active(t1::KeyName::MidMB))
	{
		if (!isMooving)
		{
			movingStartMouseCoord = InputHandler::getMouseMapCoord();
			isMooving = true;
		}
	}
	else
	{
		isMooving = false;
	}

	if (isMooving)
	{
		const sf::Vector2f newMouseMapCoord = InputHandler::getMouseMapCoord();
		const sf::Vector2f delta = movingStartMouseCoord - newMouseMapCoord;
		cameraView.move(delta);
	}
}

void Camera::moveByWASD()
{
	sf::Vector2f delta = sf::Vector2f(0.0f, 0.0f);

	if (InputHandler::active(t1::KeyName::Move_up))
		delta.y -= 1.0f;
	if (InputHandler::active(t1::KeyName::Move_left))
		delta.x -= 1.0f;
	if (InputHandler::active(t1::KeyName::Move_down))
		delta.y += 1.0f;
	if (InputHandler::active(t1::KeyName::Move_right))
		delta.x += 1.0f;

	if (delta != sf::Vector2f(0.0f, 0.0f))
		cameraView.move(delta * MOTION_SPEED_MODIFIER * mapScale);
}

void Camera::avoidEscapeFromMap()
{
	sf::Vector2f viewCenter = cameraView.getCenter();
	viewCenter.x = std::clamp(viewCenter.x, 0.0f, pixelMapSize.x);
	viewCenter.y = std::clamp(viewCenter.y, 0.0f, pixelMapSize.y);
	cameraView.setCenter(viewCenter);
}


void Camera::scale()
{
	switch (InputHandler::getMouseWheelScroll())
	{
	case t1::MouseWheelScroll::none:
		return;
	case t1::MouseWheelScroll::up:
		if (mapScale >= MIN_MAP_SCALE)
			mapScale /= SCALE_FACTOR;
		break;
	case t1::MouseWheelScroll::down:
		if (mapScale <= MAX_MAP_SCALE)
			mapScale *= SCALE_FACTOR;
		break;
	}
	cameraView.setSize(windowSize * mapScale);
}


void Camera::resize(const sf::RenderWindow& window)
{
	if (windowSize.x != window.getSize().x || windowSize.y != window.getSize().y)
	{
		windowSize = sf::Vector2f(window.getSize());
		cameraView.setSize(windowSize * mapScale);
		cameraView.setCenter(windowSize * mapScale / 2.0f);
	}
}


void Camera::updateMapRegion(const sf::RenderWindow& window)
{
	using namespace t1::be;

	sf::Vector2f startPixel = window.mapPixelToCoords(sf::Vector2i(0, 0));
	startTile = TileCoord(tile(startPixel.x) - MAX_MAP_STRUCTURE_SIZE, tile(startPixel.y) - MAX_MAP_STRUCTURE_SIZE);
	// 6 is max building_line_size. Correction is needed to correct big_buildings drawing.

	sf::Vector2f endPixel = window.mapPixelToCoords(sf::Vector2i(window.getSize().x, window.getSize().y));
	endTile = TileCoord(tile(endPixel.x) + 1, tile(endPixel.y) + 1);

	if (startTile.x < 0)
		startTile.x = 0;
	if (startTile.y < 0)
		startTile.y = 0;

	if (endTile.x > tileMapSize.x)
		endTile.x = tileMapSize.x;
	if (endTile.y > tileMapSize.y)
		endTile.y = tileMapSize.y;
}
