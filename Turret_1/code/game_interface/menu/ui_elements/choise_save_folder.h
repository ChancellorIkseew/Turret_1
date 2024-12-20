#pragma once
#ifndef CHOISE_FOLDER_MENU_H
#define CHOISE_FOLDER_MENU_H

#include <map>
#include <SFML/Graphics.hpp>

#include "game_interface/ui_window/ui_window/ui_window.h"
#include "game_interface/ui_window/elements/button/button.h"


class ChoiseFolderMenu : public UIWindow
{
private:
	std::map<int, Button> buttons;
	sf::Text helpText;

	bool isFolderSelected;
	bool isTextVisible;

	std::string selectFolder(std::string v_saveFolderName, bool& isSaveSelected);

public:
	ChoiseFolderMenu();
	~ChoiseFolderMenu() = default;

	int interact(bool& isMenuOpen, bool& startNewGame, std::string& saveFolderName);
	void relocate(sf::Vector2u windowSize) override final;

	void prepareInterfaceSprites() override final;
	void draw(sf::RenderWindow& window) override final;

};


#endif // CHOISE_FOLDER_MENU_H
