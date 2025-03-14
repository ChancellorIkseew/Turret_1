
#include "pre_settings.h"

#include "t1_system/sleep.h"
#include "game_interface/main_window/main_window.h"
#include "map_structures/pre-settings/pre-settings.h"

#include "world_pre_settings/general_pre_settings.h"
#include "world_pre_settings/terrain_pre_settings.h"
#include "world_pre_settings/buildings_pre_settings.h"
#include "world_pre_settings/mobs_pre_settings.h"

enum pageTypes
{
	START_GAME = 0,
	EXIT_TO_MENU = 1,
	GENERAL = 2,
	TERRAIN = 3,
	BUILDINGS = 4,
	MOBS = 5
};

PreSettingsWindow::PreSettingsWindow(): UIWindow(sf::Vector2i(720, 480), sf::Vector2i(0, 0))
{
	this->prepareInterfaceSprites();
	isVisible = false;

	pages[GENERAL] = std::make_unique<GeneralPreSettingsPage>(sf::Vector2i(10, 70));
	pages[TERRAIN] = std::make_unique<TerrainPreSettingsPage>(sf::Vector2i(10, 70));
	pages[BUILDINGS] = std::make_unique<BuildingsPreSettingsPage>(sf::Vector2i(10, 70));
	pages[MOBS] = std::make_unique<MobsPreSettingsPage>(sf::Vector2i(10, 70));
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


GameState PreSettingsWindow::interact(bool& isMenuOpen, PreSettings& preSettings)
{
	while (isMenuOpen)
	{
		if (buttons[START_GAME].press())
		{
			for (auto& pg : pages)
				pg.second->enter(preSettings);
			return GameState::GAMEPLAY;
		}

		if (buttons[EXIT_TO_MENU].press())
			return GameState::MAIN_MENU;

		for (auto& pg : pages)
		{
			if (buttons[pg.first].press())
			{
				for (auto& pg2 : pages)
				{
					pg2.second->setVisible(pg2.first == pg.first);
				}
			}
			
			pg.second->interact();
		}	

		t1::system::sleep(16);
	}
}



void PreSettingsWindow::relocate(const sf::Vector2i windowSize)
{
	relocateCentral(windowSize);
	for (auto& btn : buttons)
		btn.second.relocateWithOwner(position);
	for (auto& pg : pages)
		pg.second->relocateWithOwner(position);
}


void PreSettingsWindow::draw(sf::RenderWindow& window)
{
	if (!isVisible)
		return;
	drawBase(window);
	for (auto& btn : buttons)
		btn.second.draw(window);
	for (auto& pg : pages)
		pg.second->draw(window);
}
