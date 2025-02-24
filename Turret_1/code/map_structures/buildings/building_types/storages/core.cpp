
#include "core.h"
#include "map_structures/team/team.h"


Core::Core(const int16_t durability, const uint8_t size, const TileCoord tile, Team* const team) :
	Building(durability, size, tile, team) { }

void Core::interact()
{
	for (auto& res : inventory)
	{
		if (res.quantity > 0)
		{
			team->getBalance().accept(res.type, res.quantity);
			res.quantity = 0;
		}
	}
}

bool Core::canAccept(const uint16_t resType) const
{
	return true;
}
