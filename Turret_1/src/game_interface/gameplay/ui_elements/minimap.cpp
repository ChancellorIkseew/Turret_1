
#include "minimap.h"
#include "map_structures/world/world.h"
#include "game_interface/ui_window/sub_win_util/fonts.h"
#include <mutex>

static std::mutex minimap;

Minimap::Minimap() : UIWindow(sf::Vector2i(220, 220)) { }


void Minimap::initMapSize(const TileCoord mapSize)
{
	this->mapSize = mapSize;
	mapImage.resize(sf::Vector2u(mapSize.x, mapSize.y));
	map.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(mapSize.x, mapSize.y)));
	//
	int maxMapSize = mapSize.x > mapSize.y ? mapSize.x : mapSize.y;
	float scale = 200.0f / static_cast<float>(maxMapSize);
	map.setScale(sf::Vector2f(scale, scale));
}


void Minimap::interact(const World& world)
{
	if (!isVisible)
		return;
	const BuildingsMap& buildingsMap = world.getBuildingsMap();
	const BlueprintsMap& blueprintsMap = world.getBlueprintsMap();
	for (int x = 0; x < mapSize.x; ++x)
	{
		for (int y = 0; y < mapSize.y; ++y)
		{
			if (!buildingsMap.isVoidBuilding(x, y))
				mapImage.setPixel(sf::Vector2u(x, y), playerColor);
			else if (blueprintsMap.isFilledTile(TileCoord(x, y)))
				mapImage.setPixel(sf::Vector2u(x, y), sf::Color::Cyan);
			else
				mapImage.setPixel(sf::Vector2u(x, y), sf::Color::Black);
		}
	}

	for (const auto& [teamID, team] : world.getTeams())
	{
		const sf::Color& color = team->getColor();
		for (const auto& entity : team->getEneities().getList())
		{
			const TileCoord tile = entity->getTile();
			mapImage.setPixel(sf::Vector2u(tile.x, tile.y), color);
		}
	}

	std::lock_guard<std::mutex> guard(minimap);
	mapTexture.loadFromImage(mapImage);
}


void Minimap::relocate(const sf::Vector2i windowSize)
{
	position.x = windowSize.x - size.x;
	map.setPosition(sf::Vector2f(position.x + 10, position.y + 10));
}


void Minimap::draw(sf::RenderWindow& window)
{
	if (!isVisible)
		return;
	drawBase(window);
	std::lock_guard<std::mutex> guard(minimap);
	window.draw(map);
}
