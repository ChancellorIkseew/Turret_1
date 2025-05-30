
#include "res_ico.h"
#include "map_structures/resources/res_enum.h"
#include "content/texturepacks.h"

constexpr sf::Vector2i ICO_RECT(9, 9);

ResIco::ResIco(const ResType resType, const sf::Vector2i position) :
	resType(resType), localPosition(position) { }

void ResIco::setResType(const ResType resType)
{
	this->resType = resType;
}

void ResIco::relocate(const sf::Vector2i ownerPosition)
{
	absolutePosition = sf::Vector2f(localPosition + ownerPosition);
}

void ResIco::setPosition(const sf::Vector2i position)
{
	absolutePosition = sf::Vector2f(position);
}


void ResIco::prepareSprites()
{
	image.loadFromFile(Texturepacks::findImage("resources.bmp"));
	image.createMaskFromColor(sf::Color(0, 255, 0));
	texture.loadFromImage(image);
	ico.setTexture(texture);
	ico.setScale(sf::Vector2f(2.0f, 2.0f));
}

void ResIco::draw(sf::RenderWindow& window) const
{
	switch (resType)
	{
	case ResType::STONE:
		ico.setTextureRect(sf::IntRect({ 9, 0 }, ICO_RECT));
		break;
	case ResType::IRON:
		ico.setTextureRect(sf::IntRect({ 18, 0 }, ICO_RECT));
		break;
	case ResType::COPPER:
		ico.setTextureRect(sf::IntRect({ 27, 0 }, ICO_RECT));
		break;
	case ResType::SILICON:
		ico.setTextureRect(sf::IntRect({ 36, 0 }, ICO_RECT));
		break;
	case ResType::COAL:
		ico.setTextureRect(sf::IntRect({ 45, 0 }, ICO_RECT));
		break;
	case ResType::SULFUR:
		ico.setTextureRect(sf::IntRect({ 54, 0 }, ICO_RECT));
		break;

	case ResType::AC_SHELLS:
		ico.setTextureRect(sf::IntRect({ 0, 18 }, ICO_RECT));
		break;
	case ResType::HEAVY_SHELLS:
		ico.setTextureRect(sf::IntRect({ 9, 18 }, ICO_RECT));
		break;
	case ResType::ROCKET:
		ico.setTextureRect(sf::IntRect({ 18, 18 }, ICO_RECT));
		break;

	default:
		ico.setTextureRect(sf::IntRect({ 0, 0 }, ICO_RECT));
		break;
	}
;
	ico.setPosition(sf::Vector2f(absolutePosition));
	window.draw(ico);
}
