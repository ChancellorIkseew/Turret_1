
#include <iostream>
#include <fstream>

#include "pre-settings.h"


PreSettings::PreSettings(std::string saveFolderName)
{
	saveFileName = saveFileName = "saves/" + saveFolderName + "/world_pre-settings.txt";

	//terrain:
	mapSize = { 0, 0 };
	generationMetodth = 0;
	worldSeed = 0;

	//buildings:
	buildingsMaxDurabilityModidier = 1.0f;
	buildingExpansesMidifier = 1.0f;
	buildingsConstructionSpeedModifier = 1.0f;

	// enemy_mobs:
	enemyMobQuantityModifier = 1;
	enemyMobMaxDurabilityModifier = 1.0f;
	enemyMobVirtIntLevel = 0;
}


void PreSettings::loadPreSettings()
{
	std::ifstream fin;
	fin.open(saveFileName);

	if (fin.is_open())
	{
		fin >> mapSize.x >> mapSize.y >> generationMetodth >> worldSeed;
		fin >> buildingsMaxDurabilityModidier >> buildingExpansesMidifier >> buildingsConstructionSpeedModifier;
		fin >> enemyMobQuantityModifier >> enemyMobMaxDurabilityModifier >> enemyMobVirtIntLevel;
	}
	fin.close();
	std::cout << "mapMaxX: " << mapSize.x << " mapMaxY: " << mapSize.y << '\n';
}


void PreSettings::savePreSettings()
{
	std::ofstream fout;
	fout.open(saveFileName);

	if (fout.is_open())
	{
		fout << mapSize.x << " "<< mapSize.y << '\n' << generationMetodth << " " << worldSeed << '\n';
		fout << buildingsMaxDurabilityModidier << " " << buildingExpansesMidifier << " " << buildingsConstructionSpeedModifier << '\n';
		fout << enemyMobQuantityModifier << " " << enemyMobMaxDurabilityModifier << " " << enemyMobVirtIntLevel << '\n';
	}
	fout.close();

}


// terrain:
TileCoord PreSettings::getMapSize() { return mapSize; }
short PreSettings::getGenerationMetodth() { return generationMetodth; }
int PreSettings::getWorldSeed() { return worldSeed; }

void PreSettings::setMapSize(const TileCoord mapSize) { PreSettings::mapSize = mapSize; }
void PreSettings::setGenerationMetod(const short metodth) { generationMetodth = metodth; }
void PreSettings::setWorldSeed(const int seed) { worldSeed = seed; }

// buildings
float PreSettings::getBuildingsMaxDurabilityModidier() { return buildingsMaxDurabilityModidier; }
float PreSettings::getBuildingExpansesMidifier() { return buildingExpansesMidifier; }
float PreSettings::getBuildingsConstructionSpeedModifier() { return buildingsConstructionSpeedModifier; }

void PreSettings::setBuildingsMaxDurabilityModidier(float value) { buildingsMaxDurabilityModidier = value; }
void PreSettings::setBuildingExpansesMidifier(float value) { buildingExpansesMidifier = value; }
void PreSettings::setBuildingsConstructionSpeedModifier(float value) { buildingsConstructionSpeedModifier = value; }



void PreSettings::setStartBalance(std::map<int, int> startRes)
{
	GeneralPre::startBalance = startRes;
}

