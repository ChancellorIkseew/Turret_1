
#include "core.h"
#include "map_structures/team/team.h"
#include "map_structures/entities/entity/mob_enum.h"


Core::Core(const int16_t durability, const uint8_t size, const TileCoord tile, Team* const team) :
	Building(durability, size, tile, team) { }

void Core::interact()
{
	for (auto& res : inventory)
	{
		if (res.quantity <= 0)
			continue;
		team->getBalance().accept(res.type, res.quantity);
		res.quantity = 0;
	}

	for (const auto& entity : team->getEneities().getList())
	{
		if (entity->getType() == MobType::LIGHT_SHUTTLE)
			return;
	}
	const int lineCorrection = sqrt(size) / 2 - 1;
	const PixelCoord correction = t1::be::pixel(lineCorrection, lineCorrection);
	team->spawnEntity(MobType::LIGHT_SHUTTLE, t1::be::pixel(tile) + correction, Control::NONE);
}

bool Core::canAccept(const ResType resType) const
{
	return true;
}
