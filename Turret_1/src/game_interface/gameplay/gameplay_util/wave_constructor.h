#pragma once
#ifndef WAVE_CONSTRUCTOR_H
#define WAVE_CONSTRUCTOR_H

#include <typeinfo>

class Team;
class World;
struct TileCoord;

enum class MobType : uint8_t;

class WaveConstructor
{
public:
	static void spawnEnemy(const int amount, const MobType type, Team& enemy, const TileCoord mapSize);
	static void createWave(Team& enemy, World& world);
	static void switchEntities(const int wave, Team& enemy, const TileCoord mapSize);
	static void spawnTestWave(Team& enemy, const TileCoord mapSize);
};

#endif // WAVE_CONSTRUCTOR_H
