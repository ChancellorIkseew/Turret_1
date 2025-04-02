
#include "label.h"


Label::Label(const sf::String& string, const sf::Vector2i position) : position(position)
{
	text = sf::Text(turretClassic, string, 12);
	text.setFillColor(standardColor);
}

void Label::setVisible(const bool visible)
{
	isVisible = visible;
}

void Label::relocateWithOwner(const sf::Vector2i ownerPosition)
{
	text.setPosition(sf::Vector2f(ownerPosition + position));
}

void Label::draw(sf::RenderWindow& window) const
{
	if (isVisible)
		window.draw(text);
}
