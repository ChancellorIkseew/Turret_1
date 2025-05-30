#pragma once
#ifndef BLUEPRINTS_MAP_H
#define BLUEPRINTS_MAP_H

#include <vector>
#include <SFML/Graphics.hpp>
#include <cereal/archives/binary.hpp>
#include <cereal/types/vector.hpp>

#include "map_structures/base_engine/base_engine.h"
#include "blueprint.h"

class Camera;
class Team;
class BuildingsMap;

class BlueprintsMap
{
private:
	static inline Team* player;

	TileCoord mapSize;
	std::vector<std::vector<Blueprint>> blueprintsMap;

	static inline sf::Image buildingsImage;
	static inline sf::Texture buildingsTexture;
	static inline sf::Sprite buildExample = sf::Sprite(buildingsTexture);

	bool isAvaluablePlaceBlueprint(const BuildingType type, const TileCoord tile) const;
	TileCoord getMainTile(const TileCoord tile) const;

	void createBlueprint(const TileCoord mainTile, const BuildingType type, const char direction);
	void deleteBlueprint(const TileCoord mainTile);

public:
	BlueprintsMap(const TileCoord mapSize);
	BlueprintsMap() = default;
	~BlueprintsMap() = default;

	void save(cereal::BinaryOutputArchive& archive) const { archive(mapSize, blueprintsMap); }
	void load(cereal::BinaryInputArchive& archive) { archive(mapSize, blueprintsMap); }

	void placeBlueprint(const BuildingsMap& buildingsMap, const BuildingType type, const char direction, const TileCoord tile);
	void constructBuilding(BuildingsMap& buildingsMap, const TileCoord tile);

	bool tileExists(const TileCoord tile) const;
	bool isVoidTile(const TileCoord tile) const;
	bool isFilledTile(const TileCoord tile) const;
	bool isMainTile(const TileCoord tile) const;

	BuildingType getType(const TileCoord tile) const;

	static void prepareSprites();
	void draw(sf::RenderWindow& window, const Camera& camera);

	static void initTeam(Team* team) {
		BlueprintsMap::player = team;
	}
};

#endif // BLUEPRINTS_MAP_H
