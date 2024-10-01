#pragma once
#ifndef T1_BC_BUILDINGS_ICO
#define T1_BC_BUILDINGS_ICO

#include <map>
#include <SFML/Graphics.hpp>

struct BuildingIco
{
	sf::Sprite icoSprite;
	sf::IntRect texMapRect;
};

namespace t1::bc
{
	extern sf::Image buildingsIcoImage;
	extern sf::Texture buildingsIcoTexture;

	extern std::map<int, BuildingIco> buildingsIcoTable;

	void initBuildingIco();
}

#endif // T1_BC_BUILDINGS_ICO
