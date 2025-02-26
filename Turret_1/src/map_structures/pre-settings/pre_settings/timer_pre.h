#pragma once
#ifndef MAP_STR_TIMER_PRE_H
#define MAP_STR_TIMER_PRE_H

#include <cpptoml.h>

struct TimerPre
{
	uint32_t firstWave = 10800;
	uint32_t normalWave = 10800;
	uint32_t bossWave = 10800;

	void save(std::shared_ptr<cpptoml::table> root) const
	{
		auto mobsRoot = cpptoml::make_table();
		mobsRoot->insert("first-wave", firstWave);
		mobsRoot->insert("normal-wave", normalWave);
		mobsRoot->insert("boss-wave", bossWave);
		root->insert("timer", mobsRoot);
	}

	void load(std::shared_ptr<cpptoml::table> root)
	{
		const auto table = root->get_table("timer");
		//
		firstWave = table->get_as<uint32_t>("first-wave").value_or(360);
		normalWave = table->get_as<uint32_t>("normal-wave").value_or(180);
		bossWave = table->get_as<uint32_t>("boss-wave").value_or(240);
	}
};

#endif // MAP_STR_TIMER_PRE_H
