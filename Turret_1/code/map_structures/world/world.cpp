
#include "world.h"

#include <fstream>
#include <cereal/types/memory.hpp>
#include <cereal/types/unordered_set.hpp>
#include <cereal/archives/binary.hpp>

#include "t1_system/t1_mutex.h"


World::World()
{
	Entity::initWorld(this);
}

void World::save(const std::string& saveFolderName) const
{
	preSettings.save(saveFolderName);
	const std::string saveFileName = "saves/" + saveFolderName + "/world.bin";
	std::lock_guard<std::mutex> guard(t1::system::mt::buildings);
	std::ofstream fout(saveFileName, std::ios::binary);
	cereal::BinaryOutputArchive archive(fout);
	archive(teams);
	archive(terrainMap);
	archive(buildingsMap);
	fout.close();
}

void World::load(const std::string& saveFolderName)
{
	preSettings.load(saveFolderName);
	const std::string saveFileName = "saves/" + saveFolderName + "/world.bin";
	std::lock_guard<std::mutex> guard(t1::system::mt::buildings);
	std::ifstream fin(saveFileName, std::ios::binary);
	cereal::BinaryInputArchive archive(fin);
	archive(teams);
	archive(terrainMap);
	archive(buildingsMap);
	fin.close();
}

void World::createNew(PreSettings& preSettings)
{
	this->preSettings = std::move(preSettings);
	terrainMap.generate(preSettings.getTerrain());
	buildingsMap = BuildingsMap(preSettings.getTerrain().mapSize);



}

void World::simulate()
{
	std::lock_guard<std::mutex> guard(t1::system::mt::buildings);
	//buildingsMap.intetractMap();
	for (auto& team : teams)
	{
		team.second->interact(buildingsMap);
	}
	//particlesList.interact();
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

