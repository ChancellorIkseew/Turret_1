
#include <iostream>
#include <cereal/types/memory.hpp>
#include <cereal/types/list.hpp>
#include "game_interface/gameplay/gameplay_util/camera.h"
#include "game_interface/gameplay/gameplay_util/mob_controller.h"

#include "entities_list.h"


void EntitiesList::save(cereal::BinaryOutputArchive& archive) const {
	archive(entitiesList);
}
void EntitiesList::load(cereal::BinaryInputArchive& archive) {
	archive(entitiesList);
}


void EntitiesList::spawnEntity(std::unique_ptr<Entity> entity)
{
	entitiesList.push_back(std::move(entity));
}


void EntitiesList::interact(const BuildingsMap& buildingsMap)
{
	for (auto it = entitiesList.begin(); it != entitiesList.end();)
	{
		Entity& entity = **it;

		if (entity.getControlType() == Control::HARD)
		{
			entity.moveByDirectControl(MobController::getMotionVector());
		}
		else
		{
			entity.moveByOwnAI();
			entity.shoot(buildingsMap);
		}

		if (entity.getDurability() < 1)
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
