#pragma once
#ifndef MAP_STR_SHELLS_PRE_H
#define MAP_STR_SHELLS_PRE_H

#include <cpptoml.h>

struct ShellsPre
{
	float directDamageModifier = 1.0f;
	float blastDamageModifier = 1.0f;

	void save(std::shared_ptr<cpptoml::table> root) const
	{
		auto table = cpptoml::make_table();
		table->insert("direct-damage-modifier", directDamageModifier);
		table->insert("blast-damage-modifier", blastDamageModifier);
		root->insert("shells", table);
	}

	void load(std::shared_ptr<cpptoml::table> root)
	{
		const auto table = root->get_table("shells");
		//
		const auto x1 = table->get_as<double>("direct-damage-modifier");
		directDamageModifier = static_cast<float>(x1.value_or(1.0f));
		const auto x2 = table->get_as<double>("blast-damage-modifier");
		blastDamageModifier = static_cast<float>(x2.value_or(1.0f));
	}

};

#endif // MAP_STR_SHELLS_PRE_H
