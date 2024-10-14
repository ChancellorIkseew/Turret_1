#pragma once
#ifndef CHOISE_FOLDER_MENU_H
#define CHOISE_FOLDER_MENU_H

#include<vector>
#include <SFML/Graphics.hpp>

#include "game_interface/gameplay/sub_windows/sub_windows_util/sub_window.h"
#include "game_interface/gameplay/sub_windows/sub_windows_util/button/button.h"


class ChoiseFolderMenu : public SubWindow
{
private:
	std::vector<Button> buttons;
	sf::Text helpText;

	bool isFolderSelected;
	bool isTextVisible;

	std::string selectFolder(std::string v_saveFolderName, bool& isSaveSelected);

public:
	ChoiseFolderMenu();
	~ChoiseFolderMenu() = default;

	int interact(sf::Vector2i& mouseCoord, bool& isMenuOpen, bool& startNewGame, std::string& saveFolderName);
	void relocate(sf::Vector2u windowSize) override final;

	void prepareInterfaceSprites() override final;
	void draw(sf::RenderWindow& window) override final;

};


#endif // CHOISE_FOLDER_MENU_H
