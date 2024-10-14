
#include "page.h"


Page::Page(const sf::Vector2u size, const sf::Vector2u position) : SubWindow('s', size, position)
{
	ownerPosition = sf::Vector2u(0, 0);
}

void Page::relocate(const sf::Vector2u ownerPosition)
{
	position -= this->ownerPosition;
	this->ownerPosition = ownerPosition;
	position += this->ownerPosition;
}

void Page::enter() { }