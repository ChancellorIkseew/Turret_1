#pragma once
#ifndef MAP_STR_TIMER_PRE_H
#define MAP_STR_TIMER_PRE_H

#include <cpptoml.h>

struct TimerPre
{
	uint32_t firstWave = 180; // time in seconds
	uint32_t normalWave = 180; // time in seconds
	uint32_t bossWave = 180; // time in seconds

	void save(std::shared_ptr<cpptoml::table> root) const
	{
		auto table = cpptoml::make_table();
		table->insert("first-wave", firstWave);
		table->insert("normal-wave", normalWave);
		table->insert("boss-wave", bossWave);
		root->insert("timer", table);
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
