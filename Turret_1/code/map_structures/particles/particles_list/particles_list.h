#pragma once
#ifndef PARTICLES_LIST_H
#define PARTICLES_LIST_H

#include <SFML\Graphics.hpp>
#include <list>

#include "map_structures/particles/particle/particle.h"

class ParticlesList
{
private:
	std::list<std::unique_ptr<Particle>> particlesList;

public:
	ParticlesList() = default;
	~ParticlesList() = default;

	void spawnParticle(const int type, const PixelCoord coord);
	void interact();
	void animate();
	void draw(sf::RenderWindow& window);
		
};

#endif // PARTICLES_LIST_H
