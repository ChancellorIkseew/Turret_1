
#include <iostream>
#include <SFML/Graphics.hpp>

#include "sub_windows_util/fonts.h"
#include "../../main_window/main_window_resize.h"
#include "../../system/system.h"

#include "exit_confirmation.h"


ConfirmationWindow::ConfirmationWindow() : SubWindow('s', 128, 100, 0, 0)
{
    this->prepareInterfaceSprites();
    this->relocate(1200, 1200);
    isVisible = false;
}

ConfirmationWindow::~ConfirmationWindow()
{

}


void ConfirmationWindow::prepareInterfaceSprites()
{
	confirmButtonImage.loadFromFile("images/buttons/confirm.bmp");
	confirmButtonTexture.loadFromImage(confirmButtonImage);
	confirmButtonSprite.setTexture(confirmButtonTexture);
	confirmButtonSprite.setTextureRect(sf::IntRect(0, 0, 48, 48));

	rejectButtonImage.loadFromFile("images/buttons/reject.bmp");
	rejectButtonTexture.loadFromImage(rejectButtonImage);
	rejectButtonSprite.setTexture(rejectButtonTexture);
	rejectButtonSprite.setTextureRect(sf::IntRect(0, 0, 48, 48));

    confirmationText.setFont(turretClassic);
    confirmationText.setString(sf::String(L"����� ���\n����������?"));
    confirmationText.setCharacterSize(16);
    confirmationText.setFillColor(sf::Color(180, 52, 52));
}



void ConfirmationWindow::draw(sf::RenderWindow& window)
{
    if (isVisible)
    {
        this->drawSubWindowBase(window);
        window.draw(confirmButtonSprite);
        window.draw(rejectButtonSprite);
        window.draw(confirmationText);
    }
}



bool ConfirmationWindow::interactWindow(sf::Vector2i& mouseCoord)
{
    while (true)
    {
        if (LMB_Pressed)
        {

            if (confirmButtonSprite.getGlobalBounds().contains(mouseCoord.x, mouseCoord.y))
            {
                std::cout << "exit_confirmed" << std::endl;
                return true;
            }

            if (rejectButtonSprite.getGlobalBounds().contains(mouseCoord.x, mouseCoord.y))
            {
                std::cout << "exit_was_rejected" << std::endl;
                return false;
            }
        }
    }
}



void ConfirmationWindow::relocate(int windowSizeX, int windowSizeY)
{
    positionX = (windowSizeX - sizeX) / 2;
    positionY = (windowSizeY - sizeY) / 2;
    std::cout << " win x:" << positionX << " win y:" << positionY << '\n';

    confirmButtonSprite.setPosition(positionX + 10, positionY + 10);
    rejectButtonSprite.setPosition(positionX + 70, positionY + 10);
    confirmationText.setPosition(positionX + 10, positionY + 60);
}