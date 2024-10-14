
#include "game_interface/sub_window/sub_win_util/fonts.h"
#include "game_interface/main_window/main_window_resize.h"
#include "game_interface/system/system.h"
#include "game_interface/system/sleep.h"

#include "exit_confirmation.h"


ConfirmationWindow::ConfirmationWindow() : SubWindow('s', sf::Vector2u(128, 100), sf::Vector2u(0, 0))
{
    this->prepareInterfaceSprites();
    this->relocate({ 0, 0 });
    isVisible = false;
}


void ConfirmationWindow::prepareInterfaceSprites()
{
    confirm = Button("confirm.bmp", sf::Vector2i(48, 48), sf::Vector2i(10, 10));
    reject = Button("reject.bmp", sf::Vector2i(48, 48), sf::Vector2i(70, 10));

    confirmationText.setFont(turretClassic);
    confirmationText.setString(sf::String(L"Выйти без\nсохранения?"));
    confirmationText.setCharacterSize(16);
    confirmationText.setFillColor(sf::Color(180, 52, 52));
}



void ConfirmationWindow::draw(sf::RenderWindow& window)
{
    if (isVisible)
    {
        this->drawSubWindowBase(window);
        confirm.draw(window);
        reject.draw(window);
        window.draw(confirmationText);
    }
}



bool ConfirmationWindow::interact(sf::Vector2i& mouseCoord)
{
    while (true)
    {
        if (confirm.press(mouseCoord))
            return true;

        if (reject.press(mouseCoord))
            return false;

        t1::system::sleep(16);
    }
}


void ConfirmationWindow::relocate(const sf::Vector2u windowSize)
{
    SubWindow::relocateCentral(windowSize);
    confirm.relocate(position);
    reject.relocate(position);
    confirmationText.setPosition(position.x + 10, position.y + 60);
}
