#pragma once
#ifndef MAP_STR_BUILDINGS_PRE_H
#define MAP_STR_BUILDINGS_PRE_H

#include <cpptoml.h>

struct BuildingsPre
{
	float maxDurabilityModifier = 1.0f;
	float expensesModifier = 1.0f;
	float constructionSpeedModifier = 1.0f;

	void save(std::shared_ptr<cpptoml::table> root) const
	{
		auto table = cpptoml::make_table();
		table->insert("max-durability-modifier", maxDurabilityModifier);
		table->insert("expenses-modifier", expensesModifier);
		table->insert("construction-speed-modifier", constructionSpeedModifier);
		root->insert("buildings", table);
	}

	void load(std::shared_ptr<cpptoml::table> root)
	{
		const auto table = root->get_table("buildings");
		//
		const auto x1 = table->get_as<double>("max-durability-modifier");
		maxDurabilityModifier = static_cast<float>(x1.value_or(1.0f));
		const auto x2 = table->get_as<double>("expenses-modifier");
		expensesModifier = static_cast<float>(x2.value_or(1.0f));
		const auto x3 = table->get_as<double>("construction-speed-modifier");
		constructionSpeedModifier = static_cast<float>(x3.value_or(1.0f));
	}

};

#endif // MAP_STR_BUILDINGS_PRE_H
