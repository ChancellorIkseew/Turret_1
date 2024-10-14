
#include "pre_settings.h"
#include "iostream"

#include "game_interface/system/sleep.h"
#include "game_interface/main_window/main_window.h"

#include "world_pre_settings/general_pre_settings.h"
#include "world_pre_settings/terrain_pre_settings.h"

enum pageTypes
{
	START_GAME = 0,
	EXIT_TO_MENU = 1,
	GENERAL = 2,
	TERRAIN = 3,
	BUILDINGS = 4,
	MOBS = 5
};

PreSettingsWindow::PreSettingsWindow(): SubWindow('s', sf::Vector2u(720, 480), sf::Vector2u(100, 100))
{
	isVisible = false;
	this->prepareInterfaceSprites();
	this->relocate({ 0, 0 });

	pages.emplace(GENERAL, std::make_unique<GeneralPreSettingsWindow>());
	pages.emplace(TERRAIN, std::make_unique<TerrainPreSettingsWindow>());
	//pages.emplace(BUILDINGS, std::make_unique<GeneralPreSettingsWindow>());
	//pages.emplace(MOBS, std::make_unique<GeneralPreSettingsWindow>());
}

void PreSettingsWindow::prepareInterfaceSprites()
{
	buttons.resize(6);
	buttons[START_GAME] = Button("start_game.bmp", sf::Vector2i(266, 48), sf::Vector2i(70, 100));
	buttons[EXIT_TO_MENU] = Button("exit_to_menu.bmp", sf::Vector2i(48, 48), sf::Vector2i(10, 10));

	buttons[GENERAL] = Button("general.bmp", sf::Vector2i(48, 48), sf::Vector2i(70, 10));
	buttons[TERRAIN] = Button("terrain.bmp", sf::Vector2i(48, 48), sf::Vector2i(130, 10));
	buttons[BUILDINGS] = Button("buildings.bmp", sf::Vector2i(48, 48), sf::Vector2i(190, 10));
	buttons[MOBS] = Button("mobs.bmp", sf::Vector2i(48, 48), sf::Vector2i(250, 10));
	buttons.reserve(6);
}


int PreSettingsWindow::interact(sf::Vector2i& mouseCoord, bool& isMenuOpen)
{
	while (isMenuOpen)
	{
		if (buttons[START_GAME].press(mouseCoord))
		{
			//generalPreSettingsWindow.enterSettings();
			return GAMEPLAY;
		}

		if (buttons[EXIT_TO_MENU].press(mouseCoord))
			return MAIN_MENU;

		for (int i = 2; i < 6; ++i)
		{
			if (buttons[i].press(mouseCoord))
			{
				for (auto it = pages.begin(); it != pages.end(); ++it)
				{
					bool val = (i == it->first);

					it->second->setVisible(val);
				}
			}
		}

		pages[GENERAL]->interact(mouseCoord, isMenuOpen);

		t1::system::sleep(16);
	}
}



void PreSettingsWindow::relocate(const sf::Vector2u windowSize)
{
	SubWindow::relocateCentral(windowSize);
	
	for (auto& btn : buttons)
	{
		btn.relocate(position);
	}

	for (auto it = pages.begin(); it !=pages.end(); ++it)
	{
		it->second->relocate(windowSize);
	}
}


void PreSettingsWindow::draw(sf::RenderWindow& window)
{
	if (isVisible)
	{
		this->drawSubWindowBase(window);
		for (auto& btn : buttons)
		{
			btn.draw(window);
		}

		for (auto it = pages.begin(); it != pages.end(); ++it)
		{
			it->second->draw(window);
		}
	}
}
