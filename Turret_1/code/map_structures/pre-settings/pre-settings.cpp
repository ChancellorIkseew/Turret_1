
#include <iostream>
#include <fstream>

#include "pre-settings.h"


PreSettings::PreSettings(std::string saveFolderName)
{
	saveFileName = saveFileName = "saves/" + saveFolderName + "/world_pre-settings.txt";

	//terrain:
}


void PreSettings::loadPreSettings()
{
	std::ifstream fin;
	fin.open(saveFileName);

	if (fin.is_open())
	{
		//fin >> mapSize.x >> mapSize.y >> generationMetodth >> worldSeed;
		//fin >> buildingsMaxDurabilityModidier >> buildingExpansesMidifier >> buildingsConstructionSpeedModifier;
		//fin >> enemyMobQuantityModifier >> enemyMobMaxDurabilityModifier >> enemyMobVirtIntLevel;
	}
	fin.close();
	//std::cout << "mapMaxX: " << mapSize.x << " mapMaxY: " << mapSize.y << '\n';
}


void PreSettings::savePreSettings()
{
	std::ofstream fout;
	fout.open(saveFileName);

	if (fout.is_open())
	{
		//fout << mapSize.x << " "<< mapSize.y << '\n' << generationMetodth << " " << worldSeed << '\n';
		//fout << buildingsMaxDurabilityModidier << " " << buildingExpansesMidifier << " " << buildingsConstructionSpeedModifier << '\n';
		//fout << enemyMobQuantityModifier << " " << enemyMobMaxDurabilityModifier << " " << enemyMobVirtIntLevel << '\n';
	}
	fout.close();

}
