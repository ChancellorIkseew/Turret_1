
#include <SFML\Graphics.hpp>
#include <list>

#include "particle.h"

		
Particle::Particle(const int type, const PixelCoord coord) :
	type(type), coord(coord) { }

void Particle::prepareSprites()
{
	burstImage.loadFromFile("images/shell_burst.bmp");
	burstImage.createMaskFromColor(sf::Color(0, 255, 0));
	burstTexture.loadFromImage(burstImage);
	burstSprite.setTexture(burstTexture);
	burstSprite.setTextureRect(sf::IntRect(0, 0, 96, 96));
	burstSprite.setOrigin(48, 48);
	burstSprite.setColor(sf::Color(255, 255, 255, 128));
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
		burstSprite.setScale(1.0f, 1.0f);
		break;
	case 2:
		burstSprite.setScale(2.4f, 2.4f);
		break;
	default:
		burstSprite.setScale(0, 0);
		break;
	}

	burstSprite.setPosition(coord.x, coord.y);
	window.draw(burstSprite);
}
