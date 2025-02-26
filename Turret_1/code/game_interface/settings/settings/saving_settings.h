#pragma once
#ifndef T1_SAVING_SETTINGS_H
#define T1_SAVING_SETTINGS_H

#include "util/parser/cpptoml.h"

struct SavingSettings
{
	bool autosave = false;
	bool autosaveWithExit = false;
	uint32_t autosaveTime = 18000;

	void save(std::shared_ptr<cpptoml::table> root) const
	{
		auto table = cpptoml::make_table();
		table->insert("autosave", autosave);
		table->insert("autosave-with-exit", autosaveWithExit);
		table->insert("autosave-time", autosaveTime);
		root->insert("saving", table);
	}

	void load(std::shared_ptr<cpptoml::table> root)
	{
		const auto table = root->get_table("saving");
		//
		autosave = table->get_as<bool>("autosave").value_or(false);
		autosaveWithExit = table->get_as<bool>("autosave-with-exit").value_or(false);
		autosaveTime = table->get_as<uint32_t>("autosave-time").value_or(18000);
	}

};

#endif // T1_SAVING_SETTINGS_H
