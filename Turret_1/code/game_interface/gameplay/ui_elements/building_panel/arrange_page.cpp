
#include "buildings_pages.h"

void t1::bc::arrangePage(std::map<uint16_t, BuildingIco>& page)
{
	int deltaX = 10, deltaY = 10;

	for (auto& ico : page)
	{
		ico.second.setPosition(sf::Vector2u(deltaX, deltaY));

		if (deltaX < 136)
			deltaX += 42;
		else
		{
			deltaX = 10;
			deltaY += 42;
		}
	}
}