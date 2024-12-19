#pragma once
#ifndef ENTITIES_LIST_H
#define ENTITIES_LIST_H

#include <list>
#include <SFML/Graphics.hpp>
#include <cereal/archives/binary.hpp>

#include "map_structures/entities/entity/entity.h"


class EntitiesList
{
private:
	

public:
	std::list<std::unique_ptr<Entity>> entitiesList;

	EntitiesList() = default;
	~EntitiesList() = default;
	
	void save(cereal::BinaryOutputArchive& archive) const;
	void load(cereal::BinaryInputArchive& archive);

	void spawnEntity(const uint8_t amount, const uint16_t type, Team* team, const BuildingsMap& buildingsMap);
	void clean() noexcept;

	void interact(const BuildingsMap& buildingsMap);
	void draw(sf::RenderWindow& mainWindow);

	std::list<std::unique_ptr<Entity>>::iterator begin() noexcept;
	std::list<std::unique_ptr<Entity>>::iterator end() noexcept;
	
};

#endif // ENTITIES_LIST_H
