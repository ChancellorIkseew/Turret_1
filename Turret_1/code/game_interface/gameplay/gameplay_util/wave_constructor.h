#pragma once
#ifndef WAVE_CONSTRUCTOR_H
#define WAVE_CONSTRUCTOR_H

class Team;
class BuildingsMap;

class WaveConstructor
{
public:
	static void createWave(Team& enemy, const BuildingsMap& buildingsMap);
	static void switchEntities(const int wave, Team& enemy, const BuildingsMap& buildingsMap);
};

#endif // WAVE_CONSTRUCTOR_H
