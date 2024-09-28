#pragma once
#ifndef WAVE_CONSTRUCTOR_H
#define WAVE_CONSTRUCTOR_H

#include <string>


extern int waveNumber;

void createWave(int &time);
void switchEntities(const int value_waveNumber);

int loadTime(std::string saveFolderName);
void saveTime(std::string saveFolderNumber, const int v_time);

#endif // WAVE_CONSTRUCTOR_H
