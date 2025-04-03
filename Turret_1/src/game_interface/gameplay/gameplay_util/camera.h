#pragma once
#ifndef T1_CAMERA
#define T1_CAMERA

#include <SFML/Graphics.hpp>
#include "map_structures/base_engine/base_engine.h"

class Entity;

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
	void centreOnEntity(Entity* entity);
	void avoidEscapeFromMap();
	void scale();
	void resize(const sf::RenderWindow& window);
	void updateMapRegion(const sf::RenderWindow& window);

	TileCoord buildingsStartTile;
	TileCoord startTile;
	TileCoord endTile;

public:
	Camera(const TileCoord mapSize);
	~Camera() = default;

	void interact(const sf::RenderWindow& window, Entity* controlledEntity, const bool& isPaused);

	///@brief applies correction for building max size
	TileCoord getBuildingsStartTile() const { return buildingsStartTile; }
	TileCoord getStartTile() const { return startTile; }
	TileCoord getEndTile() const { return endTile; }
	const sf::View& getView() const { return cameraView; }
	float getMapScale() const { return mapScale; }

	inline bool contains(const TileCoord tile) const {
		return	tile.x >= startTile.x && tile.x <= endTile.x &&
				tile.y >= startTile.y && tile.y <= endTile.y;
	}

};

#endif // !T1_CAMERA
