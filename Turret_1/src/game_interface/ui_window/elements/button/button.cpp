
#include "button.h"

#include "t1_system/input/input_handler.h"
#include "t1_system/sleep.h"


Button::Button(const std::string& imageFile, const sf::Vector2i size, const sf::Vector2i position):
	size(size), position(position)
{
	image.loadFromFile("images/buttons/" + imageFile);
	image.createMaskFromColor(sf::Color(0, 255, 0));
	texture.loadFromImage(image);
	button.setTexture(texture);
	button.setTextureRect(sf::IntRect({ 0, 0 }, size));
}

Button& Button::operator=(const Button&& other) noexcept
{
	size = other.size;
	position = other.position;
	image = other.image;
	name = other.name;

	texture.loadFromImage(image);
	button.setTexture(texture);
	button.setTextureRect(sf::IntRect({ 0, 0 }, size));

	return *this;
}

Button::Button(const Button&& other) noexcept
{
	size = other.size;
	position = other.position;
	image = other.image;
	name = other.name;

	texture.loadFromImage(image);
	button.setTexture(texture);
	button.setTextureRect(sf::IntRect({ 0, 0 }, size));
}

bool Button::select()
{
	const sf::Vector2i mouseCoord = InputHandler::getMouseCoord();
	isSelected = button.getGlobalBounds().contains(sf::Vector2f(mouseCoord.x, mouseCoord.y));
	return isSelected;
}

bool Button::press()
{
	if (!isVisible || !select() || !InputHandler::jactive(t1::BindName::LMB))
		return false;
	isPressed = true;
	t1::system::sleep(150);
	isPressed = false;
	return true;
}

void Button::setVisible(const bool visible)
{
	isVisible = visible;
}



void Button::relocateWithOwner(const sf::Vector2i ownerPosition)
{
	button.setPosition(sf::Vector2f(ownerPosition + position));
}

void Button::draw(sf::RenderWindow& window)
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
