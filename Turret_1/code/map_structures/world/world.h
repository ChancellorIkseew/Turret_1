#pragma once
#ifndef WORLD_H
#define WORLD_H

#include <fstream>
#include <cereal/cereal.hpp>
#include <cereal/archives/binary.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/memory.hpp>

#include "map_structures/terrain/terrain.h"
#include "map_structures/buildings/buildings_map/buildings_map.h"
#include "map_structures/team/team.h"
#include "map_structures/particles/particles.h"

class World
{
private:
	TerrainMap terrainMap;
	BuildingsMap buildingsMap;
	std::unordered_set<std::shared_ptr<Team>> teams;
	//ParticlesList particlesList; not implemented

public:
	World(const TileCoord mapSize)
	{
		
	}
	World() = default;
	~World() = default;


	void save(const std::string& saveFileName) const
	{
		std::ofstream fout(saveFileName, std::ios::binary);
		cereal::BinaryOutputArchive archive(fout);
		archive(terrainMap);
		archive(buildingsMap);
		archive(teams);
		fout.close();
	}

	void load(const std::string& saveFileName)
	{
		std::ifstream fin(saveFileName, std::ios::binary);
		cereal::BinaryInputArchive archive(fin);
		archive(terrainMap);
		archive(buildingsMap);
		archive(teams);
		fin.close();
	}

	void createNew(const TileCoord mapSize)
	{
		terrainMap.generate();

	}

	void draw(sf::RenderWindow& window)
	{
		terrainMap.draw(window);
		buildingsMap.draw(window);
		for (auto it = teams.begin(); it != teams.end(); ++it)
		{
			//(*it)->draw(window);
		}
		//ParticlesList.draw();
	}

	TerrainMap& getTerrainMap() { return terrainMap; }
	BuildingsMap& getBuildingsMap() { return buildingsMap; }

};

#endif // WORLD_H
