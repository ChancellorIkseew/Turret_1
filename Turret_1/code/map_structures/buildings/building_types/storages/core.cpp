
#include "core.h"
#include "map_structures/team/team.h"


Core::Core(int type, short durability, short size, const TileCoord tile, Team* team) : Building(type, durability, size, tile, team)
{

}


void Core::interact()
{
	for (auto& res : storedResourcesList)
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
