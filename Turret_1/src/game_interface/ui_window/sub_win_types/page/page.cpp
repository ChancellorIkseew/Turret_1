
#include "page.h"


Page::Page(const sf::Vector2i size, const sf::Vector2i position) : UIPlate(size, position) { }


void Page::relocateWithOwner(const sf::Vector2i ownerPosition)
{
	position -= this->ownerPosition;
	this->ownerPosition = ownerPosition;
	position += this->ownerPosition;
}
