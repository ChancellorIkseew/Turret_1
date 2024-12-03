#pragma once
#ifndef T1_CAMERA
#define T1_CAMERA

#include <SFML/Graphics.hpp>

#include "map_structures/base_engine/base_engine.h"

class Camera
{
private:
	//sf::View camera;

	sf::Vector2i size, center;
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
