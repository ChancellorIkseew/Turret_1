
#include "button.h"

#include "t1_system/input/input_handler.h"
#include "t1_system/sleep.h"


Button::Button(const std::string& imageFile, const sf::Vector2i size, const sf::Vector2i position)
{
	this->size = size;
	this->position = position;

	image.loadFromFile("images/buttons/" + imageFile);
	image.createMaskFromColor(sf::Color(0, 255, 0));
	texture.loadFromImage(image);
	button.setTexture(texture);
	button.setTextureRect(sf::IntRect({ 0, 0 }, { size.x, size.y }));
	button.setOrigin({ 0.0f, 0.0f });
}

Button& Button::operator=(const Button&& other) noexcept
{
	size = other.size;
	position = other.position;
	image = other.image;
	name = other.name;

	texture.loadFromImage(image);
	button.setTexture(texture);
	button.setTextureRect(sf::IntRect({ 0, 0 }, { size.x, size.y }));

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
	button.setTextureRect(sf::IntRect({ 0, 0 }, { size.x, size.y }));
}

bool Button::select()
{
	const sf::Vector2i mouseCoord = InputHandler::getMouseCoord();
	isSelected = button.getGlobalBounds().contains(sf::Vector2f(mouseCoord.x, mouseCoord.y));
	return isSelected;
}

bool Button::press()
{
	if (!isVisible || !select())
		return false;

	if (InputHandler::jactive(t1::BindName::LMB))
	{
		isPressed = true;
		t1::system::sleep(150);
		isPressed = false;
		return true;
	}
	return false;
}

void Button::setVisible(const bool visible)
{
	isVisible = visible;
}



void Button::relocateWithOwner(const sf::Vector2i ownerPosition)
{
	button.setPosition(sf::Vector2f(ownerPosition.x + position.x, ownerPosition.y + position.y));
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
