#pragma once
#ifndef PARTICLE_H
#define PARTICLE_H

#include <list>
#include <SFML\Graphics.hpp>
#include "map_structures/base_engine/base_engine.h"

class Particle
{
private:
	PixelCoord coord;
	short type;
	short particlesLifeTime = 0;
	bool isWasted = false;
	
	static inline sf::Image burstImage;
	static inline sf::Texture burstTexture;
	static inline sf::Sprite burstSprite;

public:
	Particle(const int type, const PixelCoord coord);
	~Particle() = default;

	PixelCoord getCoord() const { return coord; }
	bool getIsWasted() const { return isWasted; }

	static void prepareSprites();
	void interact();
	void draw(sf::RenderWindow& window);
		
};

#endif // PARTICLE_H
