#pragma once
#ifndef WAVE_CONSTRUCTOR_H
#define WAVE_CONSTRUCTOR_H

class Team;
class World;
class BuildingsMap;

class WaveConstructor
{
public:
	static void createWave(Team& enemy, World& world);
	static void switchEntities(const int wave, Team& enemy, const BuildingsMap& buildingsMap);
};

#endif // WAVE_CONSTRUCTOR_H
