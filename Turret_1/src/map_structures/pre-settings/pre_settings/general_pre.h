#pragma once
#ifndef MAP_STR_GENERAL_PRE_H
#define MAP_STR_GENERAL_PRE_H

#include <map>
#include <cpptoml.h>
#include "map_structures/resources/res_enum.h"

enum class GameMode : uint8_t
{
	SANDBOX = 0,
	SURVIVAL = 1,
	STORM = 2,
	PVP = 3
};

struct GeneralPre
{
public:
	std::map<ResType, int> startBalance;
	GameMode gameMode = GameMode::SANDBOX;

	void save(std::shared_ptr<cpptoml::table> root) const
	{
		auto generalRoot = cpptoml::make_table();
		generalRoot->insert("quantity-modifier", static_cast<uint8_t>(gameMode));
	}

	void load(std::shared_ptr<cpptoml::table> root)
	{
		const auto table = root->get_table("general");
		//
		gameMode = static_cast<GameMode>(table->get_as<uint8_t>("quantity-modifier").value_or(1));
	}

};

#endif // MAP_STR_GENERAL_PRE_H
