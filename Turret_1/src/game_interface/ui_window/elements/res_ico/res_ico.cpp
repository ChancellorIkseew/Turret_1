
#include "res_ico.h"

#include "map_structures/resources/res_enum.h"

ResIco::ResIco(const ResType resType, const sf::Vector2u position) :
	resType(resType), position(position) { }

void ResIco::setResType(const ResType resType)
{
	this->resType = resType;
}

void ResIco::relocate(const sf::Vector2u ownerPosition)
{
	position -= this->ownerPosition;
	this->ownerPosition = ownerPosition;
	position += this->ownerPosition;
}

void ResIco::setPosition(const sf::Vector2u position)
{
	this->position = position;
}


void ResIco::prepareSprites()
{
	image.loadFromFile("images/resources.bmp");
	image.createMaskFromColor(sf::Color(0, 255, 0));
	texture.loadFromImage(image);
	ico.setTexture(texture);
	ico.setScale(2.0f, 2.0f);
}

void ResIco::draw(sf::RenderWindow& window) const
{
	switch (resType)
	{
	case ResType::STONE:
		ico.setTextureRect(sf::IntRect(9, 0, 9, 9));
		break;
	case ResType::IRON:
		ico.setTextureRect(sf::IntRect(18, 0, 9, 9));
		break;
	case ResType::COPPER:
		ico.setTextureRect(sf::IntRect(27, 0, 9, 9));
		break;
	case ResType::SILICON:
		ico.setTextureRect(sf::IntRect(36, 0, 9, 9));
		break;
	case ResType::COAL:
		ico.setTextureRect(sf::IntRect(45, 0, 9, 9));
		break;
	case ResType::SULFUR:
		ico.setTextureRect(sf::IntRect(54, 0, 9, 9));
		break;

	case ResType::AC_SHELLS:
		ico.setTextureRect(sf::IntRect(0, 18, 9, 9));
		break;
	case ResType::ROCKET:
		ico.setTextureRect(sf::IntRect(18, 18, 9, 9));
		break;

	default:
		ico.setTextureRect(sf::IntRect(0, 0, 9, 9));
		break;
	}
;
	ico.setPosition(position.x, position.y);
	window.draw(ico);
}
