
#include <fstream>
#include <string>
#include <SFML\Graphics.hpp>
#include <list>

#include "particles.h"

		
Particle::Particle(const int type, const PixelCoord coord)
{
	this->coord = coord;
	particlesLifeTime = 0;
	isWasted = false;
}


PixelCoord Particle::getCoord() const { return coord; }
bool Particle::getIsWasted() const { return isWasted; }


void Particle::prepareSprites()
{
	burstImage.loadFromFile("images/rocket_burst.bmp");
	burstImage.createMaskFromColor(sf::Color(0, 255, 0));
	burstTexture.loadFromImage(burstImage);
	burstSprite.setTexture(burstTexture);
	burstSprite.setTextureRect(sf::IntRect(0, 0, 121, 121));
	burstSprite.setOrigin(60, 60);
	burstSprite.setColor(sf::Color(255, 255, 255, 128));
}

void Particle::animate()
{
	++particlesLifeTime;
	
	if(particlesLifeTime > 40)
	{
		isWasted = true;
	}
}

void Particle::draw(sf::RenderWindow& window)
{
	burstSprite.setPosition(coord.x, coord.y);
	window.draw(burstSprite);
}


std::list<std::unique_ptr<Particle>> particlesList;


void moveParticlesList()
{
	for (auto it = particlesList.begin(); it != particlesList.end();)
	{
		if((*it)->getIsWasted() == true)
		{
			it = particlesList.erase(it);
		}
		else
		{
			(*it)->animate();
			++it;
		}
	}
}


void drawParticlesList(sf::RenderWindow& window)
{
	for (auto it = particlesList.begin(); it != particlesList.end(); ++it)
	{
		(*it)->draw(window);
	}
}


void saveParticlesList(int saveFileNumber)
{
	
}


void cleanParticlesList()
{
	particlesList.clear();
}
