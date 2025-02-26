#pragma once
#ifndef RESOURCE_UNITS_H
#define RESOURCE_UNITS_H

#include <SFML\Graphics.hpp>
#include <cereal/archives/binary.hpp>
#include "map_structures/base_engine/base_engine.h"
#include "res_enum.h"


class ResourceUnit
{
private:
	static inline sf::Image resourcesImage;
	static inline sf::Texture resourcesTexture;
	static inline sf::Sprite resourceSprite;
		
public:
	ResType type;
	char direction;
	PixelCoord coord;
	
	ResourceUnit(const ResType type, const char direction, const PixelCoord coord);
	ResourceUnit(const ResourceUnit& other);
	ResourceUnit() = default;
	~ResourceUnit() = default;

	void save(cereal::BinaryOutputArchive& archive) const;
	void load(cereal::BinaryInputArchive& archive);
	
	static void prepareSprites();
	void draw(sf::RenderWindow& window, const TileCoord tile) const;
	
};

#endif // RESOURCE_UNITS_H
