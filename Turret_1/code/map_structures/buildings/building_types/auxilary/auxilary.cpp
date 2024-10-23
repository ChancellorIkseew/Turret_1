
#include "auxilary.h"


Auxilary::Auxilary(const uint16_t type, const int16_t durability, const uint8_t size, const TileCoord tile, Team* const team) :
	Building(type, durability, size, tile, team)
{

}

void Auxilary::draw(sf::RenderWindow& window) { }
