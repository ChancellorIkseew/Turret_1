
#include "pre_settings.h"

#include "t1_system/sleep.h"
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

PreSettingsWindow::PreSettingsWindow(): SubWindow('s', sf::Vector2u(720, 480), sf::Vector2u(0, 0))
{
	this->prepareInterfaceSprites();
	this->relocate(sf::Vector2u(800, 600));
	isVisible = false;

	pages[GENERAL] = std::make_unique<GeneralPreSettingsWindow>(sf::Vector2u(10, 70));
	pages[TERRAIN] = std::make_unique<TerrainPreSettingsWindow>(sf::Vector2u(10, 70));
	//pages.emplace(BUILDINGS, std::make_unique<GeneralPreSettingsWindow>());
	//pages.emplace(MOBS, std::make_unique<GeneralPreSettingsWindow>());
}

void PreSettingsWindow::prepareInterfaceSprites()
{
	buttons[START_GAME] = Button("start_game.bmp", sf::Vector2i(266, 48), sf::Vector2i(310, 10));
	buttons[EXIT_TO_MENU] = Button("exit_to_menu.bmp", sf::Vector2i(48, 48), sf::Vector2i(10, 10));

	buttons[GENERAL] = Button("general.bmp", sf::Vector2i(48, 48), sf::Vector2i(70, 10));
	buttons[TERRAIN] = Button("terrain.bmp", sf::Vector2i(48, 48), sf::Vector2i(130, 10));
	buttons[BUILDINGS] = Button("buildings.bmp", sf::Vector2i(48, 48), sf::Vector2i(190, 10));
	buttons[MOBS] = Button("mobs.bmp", sf::Vector2i(48, 48), sf::Vector2i(250, 10));
}


int PreSettingsWindow::interact(sf::Vector2i& mouseCoord, bool& isMenuOpen)
{
	while (isMenuOpen)
	{
		if (buttons[START_GAME].press(mouseCoord))
		{
			for (auto& pg : pages)
				pg.second->enter();
			return GAMEPLAY;
		}

		if (buttons[EXIT_TO_MENU].press(mouseCoord))
			return MAIN_MENU;

		for (auto& pg : pages)
		{
			if (buttons[pg.first].press(mouseCoord))
			{
				for (auto& pg2 : pages)
				{
					pg2.second->setVisible(pg2.first == pg.first);
				}
			}
			
			pg.second->interact(mouseCoord, isMenuOpen);
		}	

		t1::system::sleep(16);
	}
}



void PreSettingsWindow::relocate(const sf::Vector2u windowSize)
{
	SubWindow::relocateCentral(windowSize);
	for (auto& btn : buttons)
		btn.second.relocate(position);
	for (auto& pg : pages)
		pg.second->relocate(position);
}


void PreSettingsWindow::draw(sf::RenderWindow& window)
{
	if (isVisible)
	{
		this->drawSubWindowBase(window);
		for (auto& btn : buttons)
			btn.second.draw(window);
		for (auto& pg : pages)
			pg.second->draw(window);
	}
}
