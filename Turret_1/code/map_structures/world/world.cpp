
#include "world.h"

#include <fstream>
#include <exception>
#include <cereal/types/memory.hpp>
#include <cereal/types/unordered_set.hpp>
#include <cereal/archives/binary.hpp>
#include "t1_system/t1_mutex.h"
#include "t1_system/events/events_handler.h"
#include "map_structures/entities/turret/turret.h"
#include "map_structures/buildings/building/building.h"


World::World()
{
	Entity::initWorld(this);
	Shell::initWorld(this);
	Building::initWorld(this);
	Turret::initWorld(this);
	Balance::initWorld(this);
}

void World::save(const std::string& saveFolderName) const
{
	preSettings.save(saveFolderName);
	const std::string saveFileName = "saves/" + saveFolderName + "/world.bin";
	std::lock_guard<std::mutex> guard(t1::system::mt::buildings);
	std::ofstream fout(saveFileName, std::ios::binary);
	cereal::BinaryOutputArchive archive(fout);
	archive(time, nextTeamID, teams, terrainMap, buildingsMap);
	fout.close();
}

void World::load(const std::string& saveFolderName)
{
	preSettings.load(saveFolderName);
	const std::string saveFileName = "saves/" + saveFolderName + "/world.bin";
	std::lock_guard<std::mutex> guard(t1::system::mt::buildings);
	std::ifstream fin(saveFileName, std::ios::binary);
	cereal::BinaryInputArchive archive(fin);
	archive(time, nextTeamID, teams, terrainMap, buildingsMap);
	fin.close();
}

void World::createNew(PreSettings& preSettings)
{
	this->preSettings = std::move(preSettings);
	terrainMap.generate(preSettings.changeTerrain());
	buildingsMap = BuildingsMap(preSettings.getTerrain().mapSize);

	addTeam("player");
	addTeam("enemy");
}

void World::simulate()
{
	std::lock_guard<std::mutex> guard(t1::system::mt::buildings);
	buildingsMap.intetract();
	for (auto& team : teams)
		team.second->interact(buildingsMap);
	particles.interact();
	time.timeRun(1);
	EventsHandler::pollSimulationEvents();
}

void World::draw(sf::RenderWindow& window, const Camera& camera)
{
	std::lock_guard<std::mutex> guard(t1::system::mt::buildings);
	terrainMap.draw(window, camera);
	buildingsMap.draw(window, camera);
	for (auto& team : teams)
		team.second->draw(window, camera);
	particles.draw(window);
}

void World::addTeam(const std::string& name)
{
	teams.emplace(nextTeamID, std::make_unique<Team>(name, nextTeamID));
	++nextTeamID;
}

Team* World::getTeam(const std::string& name)
{
	for (auto& it : teams)
	{
		if (it.second->getName() == name)
			return it.second.get();
	}
	throw std::runtime_error("team does not exist");
	return nullptr;
}
