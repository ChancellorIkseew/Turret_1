
#include <iostream>
#include <cereal/types/memory.hpp>
#include <cereal/types/list.hpp>
#include "game_interface/gameplay/gameplay_util/camera.h"

#include "entities_list.h"


void EntitiesList::save(cereal::BinaryOutputArchive& archive) const {
	archive(entitiesList);
}
void EntitiesList::load(cereal::BinaryInputArchive& archive) {
	archive(entitiesList);
}


void EntitiesList::spawnEntity(const uint8_t amount, const MobType type, Team* team, const BuildingsMap& buildingsMap)
{
	for (int i = 0; i < amount; ++i)
	{
		try
		{
			std::unique_ptr<Entity> entity = Entity::createEntity(type, team);
			entity->setCoord(Entity::randomMapBorderSpawn());
			entity->setDestCoord(t1::be::pixel(t1::ent::findClosestCore(*entity, buildingsMap)));
			entitiesList.push_back(std::move(entity));
		}
		catch (std::exception)
		{
			std::cout << "Mob_type does not exist. Type: " << static_cast<uint16_t>(type) << ".\n";
		}
	}
}


void EntitiesList::interact(const BuildingsMap& buildingsMap)
{
	for (auto it = entitiesList.begin(); it != entitiesList.end();)
	{
		(*it)->motion(buildingsMap);
		(*it)->shoot(buildingsMap);

		if ((*it)->getDurability() < 1)
			it = entitiesList.erase(it);
		else
			++it;
	}
}


void EntitiesList::draw(sf::RenderWindow& window, const Camera& camera)
{
	for (auto& entity : entitiesList)
	{
		const TileCoord tile = t1::be::tile(entity->getCoord());
		const TileCoord start = camera.getStartTile();
		const TileCoord end = camera.getEndTile();
		if (tile.x >= start.x && tile.x <= end.x && tile.y >= start.y && tile.y <= end.y)
			entity->draw(window);
	}
}
