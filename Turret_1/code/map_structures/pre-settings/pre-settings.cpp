
#include <iostream>
#include <fstream>

#include "pre-settings.h"


PreSettings::PreSettings(std::string saveFolderName)
{
	saveFileName = saveFileName = "saves/" + saveFolderName + "/world_pre-settings.txt";

	//terrain:
	mapMaxX = 0;
	mapMaxY = 0;
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
		fin >> mapMaxX >> mapMaxY >> generationMetodth >> worldSeed;
		fin >> buildingsMaxDurabilityModidier >> buildingExpansesMidifier >> buildingsConstructionSpeedModifier;
		fin >> enemyMobQuantityModifier >> enemyMobMaxDurabilityModifier >> enemyMobVirtIntLevel;
	}
	fin.close();
	std::cout << "mapMaxX: " << mapMaxX << " mapMaxY: " << mapMaxY << '\n';
}


void PreSettings::savePreSettings()
{
	std::ofstream fout;
	fout.open(saveFileName);

	if (fout.is_open())
	{
		fout << mapMaxX << " "<< mapMaxY << '\n' << generationMetodth << " " << worldSeed << '\n';
		fout << buildingsMaxDurabilityModidier << " " << buildingExpansesMidifier << " " << buildingsConstructionSpeedModifier << '\n';
		fout << enemyMobQuantityModifier << " " << enemyMobMaxDurabilityModifier << " " << enemyMobVirtIntLevel << '\n';
	}
	fout.close();

}


// terrain:
int PreSettings::getMapMaxX() { return mapMaxX; }
int PreSettings::getMapMaxY() { return mapMaxY; }
short PreSettings::getGenerationMetodth() { return generationMetodth; }
int PreSettings::getWorldSeed() { return worldSeed; }

void PreSettings::setMapMaxX(int v_mapMaxX) { mapMaxX = v_mapMaxX; }
void PreSettings::setMapMaxY(int v_mapMaxY) { mapMaxY = v_mapMaxY; }
void PreSettings::setGenerationMetod(short v_generationMetodth) { generationMetodth = v_generationMetodth; }
void PreSettings::setWorldSeed(int v_worldSeed) { worldSeed = v_worldSeed; }

// buildings
float PreSettings::getBuildingsMaxDurabilityModidier() { return buildingsMaxDurabilityModidier; }
float PreSettings::getBuildingExpansesMidifier() { return buildingExpansesMidifier; }
float PreSettings::getBuildingsConstructionSpeedModifier() { return buildingsConstructionSpeedModifier; }

void PreSettings::setBuildingsMaxDurabilityModidier(float value) { buildingsMaxDurabilityModidier = value; }
void PreSettings::setBuildingExpansesMidifier(float value) { buildingExpansesMidifier = value; }
void PreSettings::setBuildingsConstructionSpeedModifier(float value) { buildingsConstructionSpeedModifier = value; }
