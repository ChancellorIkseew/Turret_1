#pragma once
#ifndef SCRIPTS_SPAWN_ENTUTY
#define SCRIPTS_SPAWN_ENTUTY

#include <typeinfo>

enum class MobType : uint8_t;
class Team;
struct TileCoord;
struct PixelCoord;

void randomMapBorderSpawn(const MobType type, Team& enemy, const TileCoord mapSize);
PixelCoord randomMapBorderCoord(const TileCoord mapSize);

#endif // SCRIPTS_SPAWN_ENTUTY
