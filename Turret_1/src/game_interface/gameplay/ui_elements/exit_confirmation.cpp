
#include "game_interface/ui_window/sub_win_util/fonts.h"
#include "game_interface/main_window/main_window_resize.h"
#include "t1_system/sleep.h"

#include "exit_confirmation.h"


ConfirmationWindow::ConfirmationWindow() : UIWindow(sf::Vector2i(128, 100))
{
    this->prepareInterfaceSprites();
    isVisible = false;
}


void ConfirmationWindow::prepareInterfaceSprites()
{
    confirm = Button("confirm.bmp", sf::Vector2i(48, 48), sf::Vector2i(10, 10));
    reject = Button("reject.bmp", sf::Vector2i(48, 48), sf::Vector2i(70, 10));

    confirmationText = sf::Text(turretClassic, sf::String(L"Выйти без\nсохранения?"),  16);
    confirmationText.setFillColor(darkRed);
}


void ConfirmationWindow::draw(sf::RenderWindow& window)
{
    if (!isVisible)
        return;
    drawBase(window);
    confirm.draw(window);
    reject.draw(window);
    window.draw(confirmationText);
}

bool ConfirmationWindow::interact()
{
    while (true)
    {
        if (confirm.press())
            return true;
        if (reject.press())
            return false;
        t1::system::sleep(16);
    }
}


void ConfirmationWindow::relocate(const sf::Vector2i windowSize)
{
    relocateCentral(windowSize);
    confirm.relocateWithOwner(position);
    reject.relocateWithOwner(position);
    confirmationText.setPosition(sf::Vector2f(position.x + 10, position.y + 60));
}
