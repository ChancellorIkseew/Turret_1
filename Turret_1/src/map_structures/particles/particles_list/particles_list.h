#pragma once
#ifndef PARTICLES_LIST_H
#define PARTICLES_LIST_H

#include <SFML\Graphics.hpp>
#include <list>

#include "map_structures/particles/particle/particle.h"

class Camera;

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
	void draw(sf::RenderWindow& window, const Camera& camera);
		
};

#endif // PARTICLES_LIST_H
