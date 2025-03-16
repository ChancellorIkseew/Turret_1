#pragma once
#ifndef T1_GUI_SETTINGS_H
#define T1_GUI_SETTINGS_H

#include <cpptoml.h>

struct GuiSettings
{
	bool showMinimap = true;

	void save(std::shared_ptr<cpptoml::table> root) const
	{
		auto table = cpptoml::make_table();
		table->insert("show-minimap", showMinimap);
		root->insert("gui", table);
	}

	void load(std::shared_ptr<cpptoml::table> root)
	{
		const auto table = root->get_table("gui");
		if (table == nullptr) // "gui" section does not exist.
			return;
		//
		showMinimap = table->get_as<bool>("show-minimap").value_or(true);
	}

};

#endif // T1_GUI_SETTINGS_H
