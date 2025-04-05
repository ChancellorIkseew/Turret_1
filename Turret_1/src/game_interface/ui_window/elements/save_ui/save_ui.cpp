
#include "save_ui.h"


SaveUI::SaveUI(const std::string name, const sf::Vector2i position) :
	button("choise_load.bmp", sf::Vector2i(48, 48), position),
	label(name, position), position(position)
{

}

SaveUI& SaveUI::operator= (const SaveUI&& other) noexcept
{
	position = other.position;
	button = std::move(other.button);
	label = std::move(other.label);
	return *this;
}


bool SaveUI::press()
{
	return button.press();
}


void SaveUI::relocateWithOwner(const sf::Vector2i ownerPosition)
{
	button.relocateWithOwner(ownerPosition + position);
	label.relocateWithOwner(ownerPosition + position);
}

void SaveUI::draw(sf::RenderWindow& window)
{
	button.draw(window);
	label.draw(window);
}
