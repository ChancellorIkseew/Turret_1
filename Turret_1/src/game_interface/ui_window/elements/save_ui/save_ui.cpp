
#include "save_ui.h"


SaveUI::SaveUI(const std::string name, const sf::Vector2i position) :
	button("choise_load.bmp", sf::Vector2i(48, 48), position),
	label(name, position + sf::Vector2i(52, 0)), folder(name), position(position)
{
	label.setSize(18);
}

SaveUI& SaveUI::operator= (const SaveUI&& other) noexcept
{
	position = other.position;
	button = std::move(other.button);
	label = std::move(other.label);
	folder = std::move(other.folder);
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

void SaveUI::draw(sf::RenderWindow& window, int positionX, int positionY)
{
	sf::Vector2i position(positionX, positionY);

	button.relocateWithOwner(position);
	label.relocateWithOwner(position);
	button.draw(window);
	label.draw(window);
}
