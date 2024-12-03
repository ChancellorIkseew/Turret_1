#pragma once
#ifndef RESOURCE_UNITS_H
#define RESOURCE_UNITS_H

#include <SFML\Graphics.hpp>
#include "map_structures/base_engine/base_engine.h"


class ResourceUnit
{
private:
	static inline sf::Image resourcesImage;
	static inline sf::Texture resourcesTexture;
	static inline sf::Sprite resourceSprite;
		
public:
	uint16_t type;
	char direction;
	PixelCoord coord;
	
	ResourceUnit(const int type, const char direction, const PixelCoord coord);
	ResourceUnit(const ResourceUnit& other);
	ResourceUnit() = default;
	~ResourceUnit() = default;
	
	static void prepareSprites();
	void draw(sf::RenderWindow& window, const TileCoord tile) const;
	
};

#endif // RESOURCE_UNITS_H
