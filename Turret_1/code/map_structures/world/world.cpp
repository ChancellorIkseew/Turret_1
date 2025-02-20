
#include "world.h"

#include <fstream>
#include <cereal/types/memory.hpp>
#include <cereal/types/unordered_set.hpp>
#include <cereal/archives/binary.hpp>
#include "t1_system/events/events_handler.h"

#include "t1_system/t1_mutex.h"


World::World()
{
	Entity::initWorld(this);
	Shell::initWorld(this);
	Building::initWorld(this);
	Balance::initWorld(this);
}

void World::save(const std::string& saveFolderName) const
{
	preSettings.save(saveFolderName);
	const std::string saveFileName = "saves/" + saveFolderName + "/world.bin";
	std::lock_guard<std::mutex> guard(t1::system::mt::buildings);
	std::ofstream fout(saveFileName, std::ios::binary);
	cereal::BinaryOutputArchive archive(fout);
	archive(time, teams, terrainMap, buildingsMap);
	fout.close();
}

void World::load(const std::string& saveFolderName)
{
	preSettings.load(saveFolderName);
	const std::string saveFileName = "saves/" + saveFolderName + "/world.bin";
	std::lock_guard<std::mutex> guard(t1::system::mt::buildings);
	std::ifstream fin(saveFileName, std::ios::binary);
	cereal::BinaryInputArchive archive(fin);
	archive(time, teams, terrainMap, buildingsMap);
	fin.close();
}

void World::createNew(PreSettings& preSettings)
{
	this->preSettings = std::move(preSettings);
	terrainMap.generate(preSettings.changeTerrain());
	buildingsMap = BuildingsMap(preSettings.getTerrain().mapSize);



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
	{
		team.second->draw(window, camera);
	}
	//particlesList.draw();
}

