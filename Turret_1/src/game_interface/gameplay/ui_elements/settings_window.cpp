
#include "settings_window.h"

#include "game_interface/ui_window/sub_win_util/fonts.h"
#include "game_interface/settings/settings.h"
#include "game_interface/main_window/main_window_resize.h"
#include "t1_system/input/input_handler.h"
#include "t1_system/sleep.h"

enum fieldEnum
{
	WINDOW_SIZE_X = 0,
	WINDOW_SIZE_Y = 1,
	SHOW_MINIMAP = 2,
};

SettingsWindow::SettingsWindow() : UIWindow(sf::Vector2i(720, 480))
{
	this->prepareInterfaceSprites();
	isVisible = false;
}


void SettingsWindow::prepareInterfaceSprites()
{
	const int line0 = 110;
	fields[WINDOW_SIZE_X] = TextField(sf::String(L"1920"), 42, sf::Vector2i(line0, 40));
	fields[WINDOW_SIZE_Y] = TextField(sf::String(L"1016"), 42, sf::Vector2i(line0, 80));
	fields[SHOW_MINIMAP] = TextField(sf::String(L"1"), 42, sf::Vector2i(line0, 125));
	//tWindowSize = sf::Text(turretClassic, sf::String(L"Множитель\nпрочности"), 12);
}


void SettingsWindow::interact(const bool& windowOpen)
{
	while (windowOpen)
	{
		for (auto& field : fields)
			field.second.interact();
		t1::system::sleep(16);
	}
}


void SettingsWindow::relocate(const sf::Vector2i windowSize)
{
	relocateCentral(windowSize);
	for (auto& field : fields)
		field.second.relocateWithOwner(position);
}


void SettingsWindow::draw(sf::RenderWindow& window)
{
	if (!isVisible)
		return;
	drawBase(window);
	for (auto& field : fields)
		field.second.draw(window);
}
