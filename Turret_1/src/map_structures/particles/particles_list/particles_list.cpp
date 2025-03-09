
#include "particles_list.h"
#include "game_interface/gameplay/gameplay_util/camera.h"

void ParticlesList::spawnParticle(const int type, const PixelCoord coord)
{
	particlesList.emplace_back(std::make_unique<Particle>(type, coord));
}

void ParticlesList::interact()
{
	for (auto it = particlesList.begin(); it != particlesList.end();)
	{
		if ((*it)->getIsWasted())
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

void ParticlesList::draw(sf::RenderWindow& window, const Camera& camera)
{
	for (auto& particle : particlesList)
	{
		const TileCoord tile = t1::be::tile(particle->getCoord());
		const TileCoord start = camera.getStartTile() - TileCoord(6, 6);
		const TileCoord end = camera.getEndTile();
		if (tile.x >= start.x && tile.x <= end.x && tile.y >= start.y && tile.y <= end.y)
			particle->draw(window);
	}
}
