
#include <SFML\Graphics.hpp>
#include <list>

#include "particle.h"

		
Particle::Particle(const int type, const PixelCoord coord) :
	type(type), coord(coord) { }

void Particle::prepareSprites()
{
	particleImage.loadFromFile("images/shell_burst.bmp");
	particleImage.createMaskFromColor(sf::Color(0, 255, 0));
	particleTexture.loadFromImage(particleImage);
	particleSprite.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(96, 96)));
	particleSprite.setOrigin(sf::Vector2f(48, 48));
	particleSprite.setColor(sf::Color(255, 255, 255, 128));
}

void Particle::interact()
{
	++particlesLifeTime;
	if(particlesLifeTime > 40)
		isWasted = true;
}

void Particle::draw(sf::RenderWindow& window)
{
	switch (type)
	{
	case 1:
		particleSprite.setScale(sf::Vector2f(1.0f, 1.0f));
		break;
	case 2:
		particleSprite.setScale(sf::Vector2f(2.4f, 2.4f));
		break;
	default:
		particleSprite.setScale(sf::Vector2f(0, 0));
		break;
	}

	particleSprite.setPosition(sf::Vector2f(coord.x, coord.y));
	window.draw(particleSprite);
}
