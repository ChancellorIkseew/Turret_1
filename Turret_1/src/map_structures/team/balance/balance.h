#pragma once
#ifndef TEAM_BALANCE_H
#define TEAM_BALANCE_H

#include <cereal/archives/binary.hpp>
#include "map_structures/resources/all_resources.h"

class World;

class Balance
{
private:
	static inline World* world;
	AllResources balance;

public:
	Balance();
	~Balance() = default;

	void giveStartRes(const std::map<ResType, uint32_t>& startRes);

	void save(cereal::BinaryOutputArchive& archive) const;
	void load(cereal::BinaryInputArchive& archive);
	
	// Interaction
	void accept(const ResType type, uint32_t amount);
	bool isEnough(const AllResources& expenses) const;
	void waste(const AllResources& expenses);

	const AllResources& getResources() const { return balance; }

	static void initWorld(World* world) {
		Balance::world = world;
	}

};

#endif // TEAM_BALANCE_H
