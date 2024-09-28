#pragma once
#ifndef T1_CAMERA
#define T1_CAMERA

#include <SFML/Graphics.hpp>

#include "map_structures/base_engine/tile_coord.h"

class Camera
{
private:
	//sf::View camera;

	int sizeX, sizeY;
	int centerX, centerY;
	TileCoord mapSize;

	float mapScale;

	bool isMooving, isScaling;

public:
	static inline TileCoord startTile;
	static inline TileCoord endTile;

public:
	sf::View camera;

	Camera();
	~Camera() = default;

	void move();
	void scale(sf::Event event);
	void resize(sf::RenderWindow& window);
	void updateMapRegion(sf::RenderWindow& window);

};

#endif // !T1_CAMERA
