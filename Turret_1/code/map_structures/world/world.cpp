
#include "world.h"

#include <fstream>
#include <cereal/types/memory.hpp>
#include <cereal/types/unordered_set.hpp>
#include <cereal/archives/binary.hpp>

#include "t1_system/t1_mutex.h"


void World::save(const std::string& saveFolderName) const
{
	const std::string saveFileName = "saves/" + saveFolderName + "/world.bin";
	std::lock_guard<std::mutex> guard(t1::system::mt::buildings);
	std::ofstream fout(saveFileName, std::ios::binary);
	cereal::BinaryOutputArchive archive(fout);
	archive(terrainMap);
	//archive(buildingsMap);
	//archive(teams);
	fout.close();
}

void World::load(const std::string& saveFolderName)
{
	const std::string saveFileName = "saves/" + saveFolderName + "/world.bin";
	std::lock_guard<std::mutex> guard(t1::system::mt::buildings);
	std::ifstream fin(saveFileName, std::ios::binary);
	cereal::BinaryInputArchive archive(fin);
	archive(terrainMap);
	//archive(buildingsMap);
	//archive(teams);
	fin.close();
}

void World::createNew(const TileCoord mapSize)
{
	terrainMap.generate();
	buildingsMap = BuildingsMap(mapSize);
	Entity::initPreSettings();



}

void World::simulate()
{
	std::lock_guard<std::mutex> guard(t1::system::mt::buildings);
	//buildingsMap.intetractMap();
	for (auto& team : teams)
	{
		team->interact(buildingsMap);
	}
	//particlesList.interact();
}

void World::draw(sf::RenderWindow& window, const Camera& camera)
{
	std::lock_guard<std::mutex> guard(t1::system::mt::buildings);
	terrainMap.draw(window, camera);
	//buildingsMap.draw(window, camera);
	for (auto& team : teams)
	{
		team->draw(window, camera);
	}
	//particlesList.draw();
}
