
#include "res_ico.h"

#include "map_structures/resources/res_enum.h"

ResIco::ResIco(const int resType, const sf::Vector2u position)
{
	this->resType = resType;
	this->position = position;
	ownerPosition = sf::Vector2u(0, 0);

}

ResIco::ResIco()
{
	resType = 0;
}

ResIco& ResIco::operator=(const ResIco&& other) noexcept
{
	resType = other.resType;
	position = other.position;
	return *this;
}

ResIco::ResIco(const ResIco&& other) noexcept
{
	resType = other.resType;
	position = other.position;
}

void ResIco::setResType(const int resType)
{
	this->resType = resType;
}

void ResIco::relocate(const sf::Vector2u ownerPosition)
{
	position -= this->ownerPosition;
	this->ownerPosition = ownerPosition;
	position += this->ownerPosition;
}


void ResIco::prepareSprites()
{
	image.loadFromFile("images/resources_icons.bmp");				//Resources_icons
	image.createMaskFromColor(sf::Color(0, 255, 0));
	texture.loadFromImage(image);
	ico.setTexture(texture);
}

void ResIco::draw(sf::RenderWindow& window) const
{
	switch (resType)
	{
	case RES_STONE:
		ico.setTextureRect(sf::IntRect(0, 0, 18, 18));
		break;
	case RES_IRON:
		ico.setTextureRect(sf::IntRect(18, 0, 18, 18));
		break;
	case RES_COPPER:
		ico.setTextureRect(sf::IntRect(36, 0, 18, 18));
		break;
	case RES_SILICON:
		ico.setTextureRect(sf::IntRect(54, 0, 18, 18));
		break;
	case RES_COAL:
		ico.setTextureRect(sf::IntRect(72, 0, 18, 18));
		break;
	case RES_SULFUR:
		ico.setTextureRect(sf::IntRect(90, 0, 18, 18));
		break;

	case RES_AC_SHELLS:
		ico.setTextureRect(sf::IntRect(108, 0, 18, 18));
		break;
	case RES_ROCKET:
		ico.setTextureRect(sf::IntRect(126, 0, 18, 18));
		break;

	default:
		ico.setTextureRect(sf::IntRect(0, 0, 18, 18));
		break;
	}
;
	ico.setPosition(position.x, position.y);
	window.draw(ico);
}
