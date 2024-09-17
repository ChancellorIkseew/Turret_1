
#include <iostream>
#include <fstream>


#include "settings_save_system.h"




int maxGameplayWindowSizeX;
int maxGameplayWindowSizeY;

void loadSettings()
{
	std::ifstream fin;
	fin.open("saves/global_settings.txt");
	
	if(fin.is_open())
	{
		fin >> maxGameplayWindowSizeX >> maxGameplayWindowSizeY;
	}
	fin.close();
	
}



void saveSettings()
{
	std::ofstream fout;
	fout.open("saves/global_settings.txt");
	
	if(fout.is_open())
	{
		fout << maxGameplayWindowSizeX << " " << maxGameplayWindowSizeY;
	}
	fout.close();
}





















