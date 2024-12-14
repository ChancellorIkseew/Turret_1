#pragma once
#ifndef T1_CAMERA
#define T1_CAMERA

#include <SFML/Graphics.hpp>

#include "map_structures/base_engine/base_engine.h"

class Camera
{
private:
	sf::View cameraView = sf::View(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(0.0f, 0.0f));

	sf::Vector2f windowSize;
	sf::Vector2f movingStartMouseCoord = sf::Vector2f(0.0f, 0.0f);
	TileCoord tileMapSize;
	PixelCoord pixelMapSize;

	float mapScale;

	bool isMooving = false;

	void moveByMouse();
	void moveByWASD();
	void avoidEscapeFromMap();
	void scale();
	void resize(const sf::RenderWindow& window);
	void updateMapRegion(const sf::RenderWindow& window);

	static inline TileCoord startTile;
	static inline TileCoord endTile;

public:
	Camera();
	~Camera() = default;

	void interact(const sf::RenderWindow& window);

	static TileCoord getStartTile() { return startTile; }
	static TileCoord getEndTile() { return endTile; }
	sf::View getView() const { return cameraView; }

};

#endif // !T1_CAMERA
