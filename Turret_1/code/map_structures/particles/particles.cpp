
#include <fstream>
#include <string>
#include <SFML\Graphics.hpp>
#include <list>

#include "particles.h"

		
Particle::Particle(int type)
{
	isWasted = true;

	particlesLifeTime = 0;

	coordX = 0;
	coordY = 0;
}

Particle::Particle(int type, float value_coordX, float value_coordY)
{
	isWasted = false;
	
	particlesLifeTime = 0;
	
	coordX = value_coordX;
	coordY = value_coordY;
}


float Particle::getCoordX() { return coordX; }
float Particle::getCoordY() { return coordY; }
bool Particle::getIsWasted() { return isWasted; }


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

void Particle::draw(sf::RenderWindow &window, int time)
{
	burstSprite.setPosition(coordX, coordY);
	window.draw(burstSprite);
}


std::list<Particle*> particlesList;


void moveParticlesList()
{
	for (std::list<Particle*>::iterator it = particlesList.begin(); it != particlesList.end();)
	{
		if((*it)->getIsWasted() == true)
		{
			delete *it;
			it = particlesList.erase(it);
		}
		else
		{
			(*it)->animate();
			++it;
		}
	}
}


void drawParticlesList(sf::RenderWindow &window, int time)
{
	for (std::list<Particle*>::iterator it = particlesList.begin(); it != particlesList.end(); ++it)
	{
		(*it)->draw(window, time);
	}
}


void saveParticlesList(int saveFileNumber)
{
	
}


void cleanParticlesList()
{
	particlesList.clear();
}
