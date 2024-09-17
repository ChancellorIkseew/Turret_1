#pragma once

#ifndef CHOISE_FOLDER_MENU_H
#define CHOISE_FOLDER_MENU_H

#include <SFML/Graphics.hpp>
#include "../../gameplay/sub_windows/sub_windows_util/sub_window.h"


class ChoiseFolderMenu : public SubWindow
{
private:

	sf::Image clButtonImage;
	sf::Texture clButtonTexture;

	sf::Sprite cl1ButtonSprite;
	sf::Sprite cl2ButtonSprite;
	sf::Sprite cl3ButtonSprite;
	sf::Sprite cl4ButtonSprite;
	sf::Sprite cl5ButtonSprite;


	sf::Image ngButtonImage;
	sf::Texture ngButtonTexture;
	sf::Sprite ngButtonSprite;

	sf::Image lgButtonImage;
	sf::Texture lgButtonTexture;
	sf::Sprite lgButtonSprite;

	sf::Image etmButtonImage;
	sf::Texture etmButtonTexture;
	sf::Sprite etmButtonSprite;

	sf::Text helpText;

	bool isFolderSelected;
	bool isTextVisible;

	std::string selectFolder(std::string v_saveFolderName, bool& isSaveSelected);

public:

	ChoiseFolderMenu();

	void prepareInterfaceSprites() override;

	int interact(sf::Vector2i& mouseCoord, bool& isMenuOpen, bool& startNewGame, std::string& saveFolderName);

	void relocate(int windowSizeX, int windowSizeY) override;

	void draw(sf::RenderWindow& window) override;

	~ChoiseFolderMenu();

};


#endif // CHOISE_FOLDER_MENU_H