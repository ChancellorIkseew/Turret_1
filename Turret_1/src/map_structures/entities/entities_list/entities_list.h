#pragma once
#ifndef ENTITIES_LIST_H
#define ENTITIES_LIST_H

#include <list>
#include <SFML/Graphics.hpp>
#include <cereal/archives/binary.hpp>

#include "map_structures/entities/entity/entity.h"

class Camera;

class EntitiesList
{
private:
	

public:
	std::list<std::unique_ptr<Entity>> entitiesList;

	EntitiesList() = default;
	~EntitiesList() = default;
	
	void save(cereal::BinaryOutputArchive& archive) const;
	void load(cereal::BinaryInputArchive& archive);

	///@brief uses std::move to push entity into list
	void spawnEntity(std::unique_ptr<Entity> entity);
	void clean() noexcept { entitiesList.clear(); }

	void interact(const BuildingsMap& buildingsMap);
	void draw(sf::RenderWindow& window, const Camera& camera);

	const std::list<std::unique_ptr<Entity>>& getList() const { return entitiesList; }
	
};

#endif // ENTITIES_LIST_H
