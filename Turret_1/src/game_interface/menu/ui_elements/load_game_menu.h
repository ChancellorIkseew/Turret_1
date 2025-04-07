#pragma once
#ifndef CHOISE_FOLDER_MENU_H
#define CHOISE_FOLDER_MENU_H

#include <map>
#include <unordered_set>

#include "game_interface/main_window/game_state.h"
#include "game_interface/ui_window/ui_window/ui_window.h"
#include "game_interface/ui_window/elements/save_ui/save_ui.h"
#include "game_interface/ui_window/sub_win_util/fonts.h"

class LoadGameMenu : public UIWindow
{
private:
	std::map<int, Button> buttons;
	std::map<int, SaveUI> saves;
	sf::Text helpText = sf::Text(turretClassic);
	bool folderSelected;

public:
	LoadGameMenu();
	~LoadGameMenu() = default;

	GameState interact(bool& isMenuOpen, std::string& saveFolderName);
	void relocate(sf::Vector2i windowSize) override final;

	void prepareInterfaceSprites() override final;
	void draw(sf::RenderWindow& window) override final;

};


#endif // CHOISE_FOLDER_MENU_H
