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
	std::map<ResType, uint32_t> startBalance;
	GameMode gameMode = GameMode::SANDBOX;

	void save(std::shared_ptr<cpptoml::table> root) const
	{
		auto table = cpptoml::make_table();
		table->insert("game-mode", static_cast<uint8_t>(gameMode));
		root->insert("general", table);
	}

	void load(std::shared_ptr<cpptoml::table> root)
	{
		const auto table = root->get_table("general");
		//
		gameMode = static_cast<GameMode>(table->get_as<uint8_t>("game-mode").value_or(1));
	}

};

#endif // MAP_STR_GENERAL_PRE_H
