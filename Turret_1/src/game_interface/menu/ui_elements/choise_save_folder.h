#pragma once
#ifndef CHOISE_FOLDER_MENU_H
#define CHOISE_FOLDER_MENU_H

#include <map>

#include "game_interface/main_window/game_state.h"
#include "game_interface/ui_window/ui_window/ui_window.h"
#include "game_interface/ui_window/elements/button/button.h"
#include "game_interface/ui_window/sub_win_util/fonts.h"

class ChoiseFolderMenu : public UIWindow
{
private:
	std::map<int, Button> buttons;
	sf::Text helpText = sf::Text(turretClassic);

	bool isFolderSelected;
	bool isTextVisible;

	std::string selectFolder(std::string v_saveFolderName, bool& isSaveSelected);

public:
	ChoiseFolderMenu();
	~ChoiseFolderMenu() = default;

	GameState interact(bool& isMenuOpen, bool& startNewGame, std::string& saveFolderName);
	void relocate(sf::Vector2i windowSize) override final;

	void prepareInterfaceSprites() override final;
	void draw(sf::RenderWindow& window) override final;

};


#endif // CHOISE_FOLDER_MENU_H
