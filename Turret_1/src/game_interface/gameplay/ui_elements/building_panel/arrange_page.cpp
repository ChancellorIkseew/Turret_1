
#include "buildings_pages.h"

void t1::bc::arrangePage(std::map<BuildingType, BuildingIco>& page)
{
	int deltaX = 62, deltaY = 10;

	for (auto& [type, ico] : page)
	{
		ico.setPosition(sf::Vector2i(deltaX, deltaY));

		if (deltaX < 188)
			deltaX += 42;
		else
		{
			deltaX = 62;
			deltaY += 42;
		}
	}
}