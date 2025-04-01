
#include "minimap.h"
#include "map_structures/world/world.h"
#include "game_interface/ui_window/sub_win_util/fonts.h"
#include "game_interface/settings/settings.h"
#include <mutex>

static std::mutex minimap;
constexpr float MINIMAP_PIXEL_SIZE = 200.0f;

Minimap::Minimap() : UIWindow(sf::Vector2i(220, 220)) { }


void Minimap::initMapSize(const TileCoord mapSize)
{
	this->mapSize = mapSize;
	mapImage.resize(sf::Vector2u(mapSize.x, mapSize.y));
	map.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(mapSize.x, mapSize.y)));
	//
	int maxMapSize = mapSize.x > mapSize.y ? mapSize.x : mapSize.y;
	float scale = MINIMAP_PIXEL_SIZE / static_cast<float>(maxMapSize);
	map.setScale(sf::Vector2f(scale, scale));
	markerSize = maxMapSize / 50;
}


void Minimap::setMarker(const TileCoord tile, const sf::Color color)
{
	TileCoord start, end;
	start.x = std::clamp(tile.x - markerSize, 0, mapSize.x - 1);
	start.y = std::clamp(tile.y - markerSize, 0, mapSize.y - 1);
	end.x = std::clamp(tile.x + markerSize, 0, mapSize.x - 1);
	end.y = std::clamp(tile.y + markerSize, 0, mapSize.y - 1);

	for (int x = start.x; x < end.x; ++x)
		for (int y = start.y; y < end.y; ++y)
			mapImage.setPixel(sf::Vector2u(x, y), color);
}

void Minimap::interact(const World& world)
{
	if (!isVisible || !Settings::getGui().showMinimap)
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
			setMarker(entity->getTile(), color);
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
	if (!isVisible || !Settings::getGui().showMinimap)
		return;
	drawBase(window);
	std::lock_guard<std::mutex> guard(minimap);
	window.draw(map);
}
