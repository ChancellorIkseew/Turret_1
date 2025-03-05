#pragma once
#ifndef WAVE_CONSTRUCTOR_H
#define WAVE_CONSTRUCTOR_H

#include <typeinfo>

class Team;
class World;
class BuildingsMap;

enum class MobType : uint8_t;

class WaveConstructor
{
public:
	static void spawnEnemy(const int amount, const MobType type, Team& enemy, const BuildingsMap& buildingsMap);
	static void createWave(Team& enemy, World& world);
	static void switchEntities(const int wave, Team& enemy, const BuildingsMap& buildingsMap);
	static void spawnTestWave(Team& enemy, const BuildingsMap& buildingsMap);
};

#endif // WAVE_CONSTRUCTOR_H
