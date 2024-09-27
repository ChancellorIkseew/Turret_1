
#include <iostream>
#include <crtdbg.h>

#include "code/game_interface/main_window/main_window.h"

//#define TURRET_1_NO_TEST_BUILD
//#define TURRET_1_MOB_TYPES_TEST


int main()
{
    //setlocale(LC_ALL, "Russian");
    //system("chcp 1251");
    //SetConsoleCP(1251);
    //SetConsoleOutputCP(1251);

    

    openMainWindow();

    std::cout << "return_to_main_works" << '\n';

    _CrtDumpMemoryLeaks();
    return 0;
}
