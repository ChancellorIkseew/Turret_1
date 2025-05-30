
#include "world.h"

#include <fstream>
#include <exception>
#include <cereal/types/memory.hpp>
#include <cereal/types/unordered_set.hpp>
#include <cereal/archives/binary.hpp>
#include "t1_system/t1_mutex.h"
#include "t1_system/events/events_handler.h"
#include "t1_system/files/files.h"
#include "map_structures/entities/turret/turret.h"
#include "map_structures/buildings/building/building.h"
#include "game_interface/ui_window/sub_win_util/fonts.h"

namespace stdfs = std::filesystem;
stdfs::path saves("saves");

World::World()
{
	Entity::initWorld(this);
	Shell::initWorld(this);
	Building::initWorld(this);
	Turret::initWorld(this);
	Balance::initWorld(this);
}

void World::save(const std::string& folder) const
{
	t1::system::tryCreateFolder(saves);
	t1::system::tryCreateFolder(saves / folder);
	preSettings.save(folder);
	const stdfs::path saveFile = saves / folder / "world.bin";
	std::lock_guard<std::mutex> guard(t1::system::mt::buildings);
	std::ofstream fout(saveFile, std::ios::binary);
	cereal::BinaryOutputArchive archive(fout);
	archive(time, nextTeamID, teams, terrainMap, buildingsMap, blueprintsMap);
}

void World::load(const std::string& folder)
{
	preSettings.load(folder);
	const stdfs::path saveFile = saves / folder / "world.bin";
	std::ifstream fin(saveFile, std::ios::binary);
	cereal::BinaryInputArchive archive(fin);
	archive(time, nextTeamID, teams, terrainMap, buildingsMap, blueprintsMap);
}

void World::createNew(const PreSettings& preSettings)
{
	this->preSettings = preSettings;
	terrainMap.generate(preSettings.getTerrain());
	buildingsMap = BuildingsMap(preSettings.getTerrain().mapSize);
	blueprintsMap = BlueprintsMap(preSettings.getTerrain().mapSize);

	addTeam("player", playerColor);
	addTeam("enemy", enemyColor);
}

void World::simulate()
{
	std::lock_guard<std::mutex> guard(t1::system::mt::buildings);
	buildingsMap.intetract();
	for (auto& [teamID, team] : teams)
		team->interact(buildingsMap);
	particles.interact();
	time.timeRun(1);
	EventsHandler::clearEvents();
	buildingsMap.pushChanges();
	//  for (auto& [teamID, team] : teams)
	//		team->pushChanges();
}

void World::draw(sf::RenderWindow& window, const Camera& camera)
{
	std::lock_guard<std::mutex> guard(t1::system::mt::buildings);
	terrainMap.draw(window, camera);
	buildingsMap.draw(window, camera);
	blueprintsMap.draw(window, camera);
	for (auto& [teamID, team] : teams)
		team->draw(window, camera);
	particles.draw(window, camera);
}

void World::addTeam(const std::string& name, const sf::Color& color)
{
	teams.emplace(nextTeamID, std::make_unique<Team>(name, color, nextTeamID));
	++nextTeamID;
}

Team* World::getTeam(const std::string& name)
{
	for (auto& [teamID, team] : teams)
	{
		if (team->getName() == name)
			return team.get();
	}
	throw std::runtime_error("team does not exist");
	return nullptr;
}
