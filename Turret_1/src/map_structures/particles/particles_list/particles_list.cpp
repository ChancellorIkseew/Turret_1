
#include "particles_list.h"

void ParticlesList::spawnParticle(const int type, const PixelCoord coord)
{
	particlesList.emplace_back(std::make_unique<Particle>(type, coord));
}

void ParticlesList::interact()
{
	for (auto it = particlesList.begin(); it != particlesList.end();)
	{
		if ((*it)->getIsWasted() == true)
		{
			it = particlesList.erase(it);
		}
		else
		{
			(*it)->interact();
			++it;
		}
	}
}

void ParticlesList::animate()
{
	
}

void ParticlesList::draw(sf::RenderWindow& window)
{
	for (auto& particle : particlesList)
		particle->draw(window);
}
