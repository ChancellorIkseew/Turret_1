
#include <iostream>
#include <crtdbg.h>

#include "code/game_interface/main_window/main_window.h"
#include "game_interface/settings/settings.h"

int main()
{
    Settings::load();
    openMainWindow();

    std::cout << "return_to_main_works\n";

    _CrtDumpMemoryLeaks();
    return 0;
}
