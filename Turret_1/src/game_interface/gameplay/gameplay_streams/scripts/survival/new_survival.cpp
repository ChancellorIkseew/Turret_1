
#include "new_survival.h"

#include "map_structures/world/world.h"
#include "map_structures/pre-settings/pre-settings.h"
#include "map_structures/entities/entity/mob_enum.h"


void createPlayerBase(World& world, const PreSettings& preSettings)
{
	const TileCoord mapCentre = preSettings.getTerrain().mapSize / 2 - TileCoord(2, 2);
	Team* player = world.getTeam("player");
	world.getBuildingsMap().placeBuilding(BuildingType::CORE_MK2, 0, mapCentre, player);
	player->getBalance().giveStartRes(preSettings.getGeneral().startBalance);
	player->spawnEntity(MobType::LIGHT_SHUTTLE, t1::be::pixel(mapCentre), Control::NONE);
}