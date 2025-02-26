#pragma once
#ifndef MAP_STR_GENERAL_PRE_H
#define MAP_STR_GENERAL_PRE_H

#include <map>
#include "util/parser/cpptoml.h"
#include "map_structures/resources/res_enum.h"

enum class GameMode
{
	SANDBOX,
	SURVIVAL,
	STORM,
	PVP
};

struct GeneralPre
{
public:
	std::map<ResType, int> startBalance;
	GameMode gameMode = GameMode::SANDBOX;

	void save(std::shared_ptr<cpptoml::table> root) const
	{

	}

	void load(std::shared_ptr<cpptoml::table> root)
	{

	}

};

#endif // MAP_STR_GENERAL_PRE_H
