
#include "buildings_pages.h"

void t1::bc::arrangePage(std::map<uint16_t, BuildingIco>& page)
{
	int deltaX = 62, deltaY = 10;

	for (auto& ico : page)
	{
		ico.second.setPosition(sf::Vector2u(deltaX, deltaY));

		if (deltaX < 188)
			deltaX += 42;
		else
		{
			deltaX = 62;
			deltaY += 42;
		}
	}
}