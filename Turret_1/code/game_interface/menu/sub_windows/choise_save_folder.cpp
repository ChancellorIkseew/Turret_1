
#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <list>

#include "choise_save_folder.h"

#include "game_interface/gameplay/sub_windows/sub_windows_util/fonts.h"
#include "game_interface/system/system.h"
#include "game_interface/main_window/main_window.h"

#include "map_structures/pre-settings/pre-settings.h"

std::string ChoiseFolderMenu::selectFolder(std::string v_saveFileName, bool& isFolderSelected)
{
	std::string saveFolderName;

	if (isFolderSelected == false)
	{
		saveFolderName = v_saveFileName;
		isFolderSelected = true;
	}
	else
	{
		saveFolderName = "0";
		isFolderSelected = false;
	}

	return saveFolderName;
}


ChoiseFolderMenu::ChoiseFolderMenu() : SubWindow('s', 720, 480, 100, 100)
{
	isFolderSelected = false;
	isTextVisible = false;
	this->prepareInterfaceSprites();
	this->relocate(1920, 1080);
	isVisible = false;
}



void ChoiseFolderMenu::prepareInterfaceSprites()
{
	ngButtonImage.loadFromFile("images/buttons/new_game.bmp");
	ngButtonTexture.loadFromImage(ngButtonImage);
	ngButtonSprite.setTexture(ngButtonTexture);
	ngButtonSprite.setTextureRect(sf::IntRect(0, 0, 242, 48));
	
	lgButtonImage.loadFromFile("images/buttons/load_game.bmp");
	lgButtonTexture.loadFromImage(lgButtonImage);
	lgButtonSprite.setTexture(lgButtonTexture);
	lgButtonSprite.setTextureRect(sf::IntRect(0, 0, 364, 48));
	
	etmButtonImage.loadFromFile("images/buttons/exit_to_menu.bmp");
	etmButtonTexture.loadFromImage(etmButtonImage);
	etmButtonSprite.setTexture(etmButtonTexture);
	etmButtonSprite.setTextureRect(sf::IntRect(0, 0, 48, 48));

	clButtonImage.loadFromFile("images/buttons/choise_load.bmp");
	clButtonTexture.loadFromImage(clButtonImage);

	cl1ButtonSprite.setTexture(clButtonTexture);
	cl1ButtonSprite.setTextureRect(sf::IntRect(0, 0, 48, 48));

	cl2ButtonSprite.setTexture(clButtonTexture);
	cl2ButtonSprite.setTextureRect(sf::IntRect(0, 0, 48, 48));

	cl3ButtonSprite.setTexture(clButtonTexture);
	cl3ButtonSprite.setTextureRect(sf::IntRect(0, 0, 48, 48));

	cl4ButtonSprite.setTexture(clButtonTexture);
	cl4ButtonSprite.setTextureRect(sf::IntRect(0, 0, 48, 48));

	cl5ButtonSprite.setTexture(clButtonTexture);
	cl5ButtonSprite.setTextureRect(sf::IntRect(0, 0, 48, 48));

	helpText.setFont(turretClassic);
	helpText.setString(sf::String(L"„тобы начать игру, нужно выбрать сохранение,\nв которое будет записыватьс€ игровой прогресс."));
	helpText.setCharacterSize(16);
	helpText.setFillColor(sf::Color(68, 52, 52));
}



int ChoiseFolderMenu::interact(sf::Vector2i& mouseCoord, bool& isMenuOpen, bool& startNewGame, std::string& saveFolderName)
{
	while (isMenuOpen)
	{
		if (LMB_Pressed)
		{
			if (cl1ButtonSprite.getGlobalBounds().contains(mouseCoord.x, mouseCoord.y))
			{
				std::cout << "load button 1 works" << std::endl;
				cl1ButtonSprite.setColor(sf::Color(239, 228, 176));
				saveFolderName = selectFolder("save1", isFolderSelected);
				isTextVisible = false;
			}

			if (cl2ButtonSprite.getGlobalBounds().contains(mouseCoord.x, mouseCoord.y))
			{
				std::cout << "load button 2 works" << std::endl;
				cl2ButtonSprite.setColor(sf::Color(239, 228, 176));
				saveFolderName = selectFolder("save2", isFolderSelected);
				isTextVisible = false;
			}

			if (cl3ButtonSprite.getGlobalBounds().contains(mouseCoord.x, mouseCoord.y))
			{
				std::cout << "load button 3 works" << std::endl;
				cl3ButtonSprite.setColor(sf::Color(239, 228, 176));
				saveFolderName = selectFolder("save3", isFolderSelected);
				isTextVisible = false;
			}

			if (cl4ButtonSprite.getGlobalBounds().contains(mouseCoord.x, mouseCoord.y))
			{
				std::cout << "load button 4 works" << std::endl;
				cl4ButtonSprite.setColor(sf::Color(239, 228, 176));
				saveFolderName = selectFolder("save4", isFolderSelected);
				isTextVisible = false;
			}

			if (cl5ButtonSprite.getGlobalBounds().contains(mouseCoord.x, mouseCoord.y))
			{
				std::cout << "load button 5 works" << std::endl;
				cl5ButtonSprite.setColor(sf::Color(239, 228, 176));
				saveFolderName = selectFolder("save5", isFolderSelected);
				isTextVisible = false;
			}



			if (lgButtonSprite.getGlobalBounds().contains(mouseCoord.x, mouseCoord.y))
			{
				if (isFolderSelected)
				{
					std::cout << "load_game button works" << std::endl;
					PreSettings preSettings1(saveFolderName);
					startNewGame = false;
					return GameCondition::GAMEPLAY;
				}
				else
				{
					isTextVisible = true;
				}
			}


			if (ngButtonSprite.getGlobalBounds().contains(mouseCoord.x, mouseCoord.y))
			{
				if (isFolderSelected)
				{
					std::cout << "new_game button works" << std::endl;
					PreSettings preSettings1(saveFolderName);
					startNewGame = true;
					return PRE_SETTINGS_MENU;
				}
				else
				{
					isTextVisible = true;
				}
			}


			if (etmButtonSprite.getGlobalBounds().contains(mouseCoord.x, mouseCoord.y))
			{
				std::cout << "exit to menu button works" << std::endl;
				return MAIN_MENU;
			}

			Sleep(150);
		}

		if (!isFolderSelected)
		{
			cl1ButtonSprite.setColor(sf::Color::White);
			cl2ButtonSprite.setColor(sf::Color::White);
			cl3ButtonSprite.setColor(sf::Color::White);
			cl4ButtonSprite.setColor(sf::Color::White);
			cl5ButtonSprite.setColor(sf::Color::White);
		}

		Sleep(16);
	}

	return CHOISE_FOLDER_MENU;
}



void ChoiseFolderMenu::relocate(int windowSizeX, int windowSizeY)
{
	positionX = (windowSizeX - sizeX) / 2;
	positionY = (windowSizeY - sizeY) / 2;
	//std::cout << " win x:" << positionX << " win y:" << positionY << '\n';

	ngButtonSprite.setPosition(positionX + 10, positionY + 100);
	lgButtonSprite.setPosition(positionX + 10, positionY + 170);
	etmButtonSprite.setPosition(positionX + sizeX - 58, positionY + 10);

	cl1ButtonSprite.setPosition(positionX + 10, positionY + 240);
	cl2ButtonSprite.setPosition(positionX + 70, positionY + 240);
	cl3ButtonSprite.setPosition(positionX + 130, positionY + 240);
	cl4ButtonSprite.setPosition(positionX + 190, positionY + 240);
	cl5ButtonSprite.setPosition(positionX + 250, positionY + 240);

	helpText.setPosition(positionX + 70, positionY + 350);
}



void ChoiseFolderMenu::draw(sf::RenderWindow& window)
{
	if (isVisible)
	{
		this->drawSubWindowBase(window);
		if (isTextVisible)
		{
			window.draw(helpText);
		}

		window.draw(cl1ButtonSprite);
		window.draw(cl2ButtonSprite);
		window.draw(cl3ButtonSprite);
		window.draw(cl4ButtonSprite);
		window.draw(cl5ButtonSprite);

		window.draw(etmButtonSprite);
		window.draw(ngButtonSprite);
		window.draw(lgButtonSprite);
	}
}



ChoiseFolderMenu::~ChoiseFolderMenu()
{

}
