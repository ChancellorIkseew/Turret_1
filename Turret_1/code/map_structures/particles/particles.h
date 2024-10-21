#pragma once
#ifndef PARTICLES_H
#define PARTICLES_H

#include <SFML\Graphics.hpp>
#include <list>

#include "map_structures/base_engine/tile_coord.h"


class Particle
{
private:
	PixelCoord coord;
	
	short type;
	short particlesLifeTime;
	bool isWasted;
	
	static inline sf::Image burstImage;
	static inline sf::Texture burstTexture;
	static inline sf::Sprite burstSprite;

public:
	Particle(const int type, const PixelCoord coord);
	~Particle() = default;

	PixelCoord getCoord() const;
	bool getIsWasted() const;

	static void prepareSprites();
	void animate();
	void draw(sf::RenderWindow& window);
		
};


extern std::list<std::unique_ptr<Particle>> particlesList;

void moveParticlesList();
void drawParticlesList(sf::RenderWindow& window);
void cleanParticlesList();

#endif // PARTICLES_H
