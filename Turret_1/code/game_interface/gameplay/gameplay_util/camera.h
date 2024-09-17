#pragma once
#ifndef T1_CAMERA
#define T1_CAMERA

#include <SFML/Graphics.hpp>

#include "../../../map_structures/base_engine/tile_coord.h"

class Camera
{
private:

	//sf::View camera;

	int sizeX, sizeY;

	int centerX, centerY;

	float mapScale;

	bool isMooving, isScaling;

public:

	static inline TileCoord startTile;
	static inline TileCoord endTile;

public:

	sf::View camera;

	Camera();

	void move();

	void scale(sf::Event event);

	void resize(sf::RenderWindow& window);

	void updateMapRegion(sf::RenderWindow& window);

	~Camera();

};

#endif // !T1_CAMERA
