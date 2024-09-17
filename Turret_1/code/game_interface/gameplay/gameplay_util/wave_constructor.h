#pragma once

#ifndef WAVE_CONSTRUCTOR_H
#define WAVE_CONSTRUCTOR_H

#include <iostream>
#include <fstream>
#include <string>
#include <SFML\Graphics.hpp>
#include <list>





extern int waveNumber;


void createWave(int &time);

void switchEntities(int value_waveNumber);




int loadTime(std::string saveFolderName);

void saveTime(std::string saveFolderNumber, int v_time);


#endif // WAVE_CONSTRUCTOR_H
