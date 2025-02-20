#pragma once
#ifndef WORLD_H
#define WORLD_H

#include <unordered_map>

#include "map_structures/team/team.h"
#include "map_structures/terrain/terrain.h"
#include "map_structures/buildings/buildings_map/buildings_map.h"
#include "map_structures/particles/particles.h"
#include "map_structures/pre-settings/pre-settings.h"
#include "game_interface/gameplay/gameplay_util/t1_time.h"

class WaveConstructor;

class World
{
private:
	PreSettings preSettings;
	TerrainMap terrainMap;
	BuildingsMap buildingsMap;
	std::unordered_map<int, std::shared_ptr<Team>> teams;
	//ParticlesList particles; not implemented
	t1::Time time;

public:
	World();
	~World() = default;

	void save(const std::string& saveFolderName) const;
	void load(const std::string& saveFolderName);
	void createNew(PreSettings& preSettings);

	void simulate();
	void draw(sf::RenderWindow& window, const Camera& camera);

	BuildingsMap& getBuildingsMap() { return buildingsMap; } // non_const
	
	const PreSettings& getPreSettings() const { return preSettings; };
	const TerrainMap& getTerrainMap() const { return terrainMap; }
	const BuildingsMap& getBuildingsMap() const { return buildingsMap; }
	const t1::Time& getTime() const { return time; }

	void addTeam(const sf::String& name) {
		teams.emplace(0, std::make_shared<Team>(name));
	}
	void addTeam(const std::shared_ptr<Team> team) {
		teams.emplace(team->getID(), team);
	}
	Team* getTeam(const int ID) const{
		return teams.find(ID)->second.get();
	}
	const std::unordered_map<int, std::shared_ptr<Team>>& getTeams() const {
		return teams;
	}

	friend WaveConstructor;
};

#endif // WORLD_H
