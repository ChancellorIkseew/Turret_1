
#include "checkbox.h"

#include "t1_system/input/input_handler.h"
#include "t1_system/sleep.h"

constexpr sf::Vector2i size(22, 22);

Checkbox::Checkbox(const bool startValue, const sf::Vector2i position) :
	isPressed(startValue), localPosition(position) { }

bool Checkbox::select()
{
	const sf::Vector2i mouse = InputHandler::getMouseCoord();
	const sf::Vector2f start = absolutePosition;
	const sf::Vector2f end = start+ sf::Vector2f(size);
	isSelected = mouse.x > start.x && mouse.x < end.x && mouse.y > start.y && mouse.y < end.y;
	return isSelected;
}

bool Checkbox::press()
{
	if (!isVisible || !select() || !InputHandler::jactive(t1::BindName::LMB))
		return false;
	isPressed = !isPressed;
	return isPressed;
}


void Checkbox::relocateWithOwner(const sf::Vector2i ownerPosition)
{
	absolutePosition = sf::Vector2f(localPosition + ownerPosition);
}

void Checkbox::prepareSprites()
{
	image.loadFromFile("images/buttons/checkbox.bmp");
	texture.loadFromImage(image);
}

void Checkbox::draw(sf::RenderWindow& window) const
{
	if (isPressed)
		button.setTextureRect(sf::IntRect(sf::Vector2i(0, size.y * 2), size));
	else if (isSelected)
		button.setTextureRect(sf::IntRect(sf::Vector2i(0, size.y), size));
	else
		button.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), size));

	button.setPosition(absolutePosition);
	window.draw(button);
}
