#pragma once
#ifndef MAP_STR_MOBS_PRE_H
#define MAP_STR_MOBS_PRE_H

#include <cpptoml.h>

struct MobsPre
{
	uint8_t quantityModifier = 1;
	float maxDurabilityModifier = 1.0f;
	float collisionDamageModifier = 1.0f;
	uint8_t virtIntLevel = 1;

	void save(std::shared_ptr<cpptoml::table> root) const
	{
		auto table = cpptoml::make_table();
		table->insert("quantity-modifier", quantityModifier);
		table->insert("max-durability-modifier", maxDurabilityModifier);
		table->insert("collision-damage", collisionDamageModifier);
		table->insert("ai-level", virtIntLevel);
		root->insert("mobs", table);
	}

	void load(std::shared_ptr<cpptoml::table> root)
	{
		const auto table = root->get_table("mobs");
		//
		quantityModifier = table->get_as<uint8_t>("quantity-modifier").value_or(1);
		const auto x1 = table->get_as<double>("max-durability-modifier");
		maxDurabilityModifier = static_cast<float>(x1.value_or(1.0f));
		const auto x2 = table->get_as<double>("collision-damage");
		collisionDamageModifier = static_cast<float>(x2.value_or(1.0f));
		virtIntLevel = table->get_as<uint8_t>("ai-level").value_or(1);
	}

};

#endif // MAP_STR_MOBS_PRE_H
