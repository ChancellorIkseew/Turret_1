
#include "checkbox.h"

#include "t1_system/input/input_handler.h"
#include "t1_system/sleep.h"

constexpr sf::Vector2i size(22, 22);

Checkbox::Checkbox(const bool startValue, const sf::Vector2i position) :
	isPressed(startValue), position(position) { }

bool Checkbox::select()
{
	const sf::Vector2i mouseCoord = InputHandler::getMouseCoord();
	isSelected = button.getGlobalBounds().contains(sf::Vector2f(mouseCoord.x, mouseCoord.y));
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
	button.setPosition(sf::Vector2f(ownerPosition.x + position.x, ownerPosition.y + position.y));
}

void Checkbox::prepareSprites()
{
	image.loadFromFile("images/buttons/checkbox.bmp");
	texture.loadFromImage(image);
	button.setTexture(texture);
}

void Checkbox::draw(sf::RenderWindow& window)
{
	if (!isVisible)
		return;

	if (isPressed)
		button.setTextureRect(sf::IntRect(sf::Vector2i(0, size.y * 2), size));
	else if (isSelected)
		button.setTextureRect(sf::IntRect(sf::Vector2i(0, size.y), size));
	else
		button.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), size));

	window.draw(button);
}
