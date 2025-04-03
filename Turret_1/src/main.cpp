
#include <iostream>
#include "game_interface/main_window/main_window.h"
#include "game_interface/settings/settings.h"
#include "content/texturepacks.h"

int main()
{
    Settings::load();
    Texturepacks::loadConfig();
    Texturepacks::loadTextures();
    MainWindow::open();

    std::cout << "return_to_main_works\n";
    return 0;
}
