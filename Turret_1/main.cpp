
#include <iostream>

#include "code/game_interface/main_window/main_window.h"

//#define TURRET_NO_TEST_BUILD


int main()
{
	//setlocale(LC_ALL, "Russian");
	//system("chcp 1251");
	//SetConsoleCP(1251);
	//SetConsoleOutputCP(1251);

	

	openMainWindow();

	std::cout << "return_to_main_works" << '\n';

	
    return 0;
}