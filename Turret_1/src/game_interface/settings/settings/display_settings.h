#pragma once
#ifndef T1_DISPLAY_SETTINGS_H
#define T1_DISPLAY_SETTINGS_H

#include <SFML/Graphics.hpp>
#include <cpptoml.h>

struct DisplaySettings
{
	sf::Vector2u windowMaxSize = sf::Vector2u(1920, 1016);
	bool fullscreen = false;

	void save(std::shared_ptr<cpptoml::table> root) const
	{
		auto table = cpptoml::make_table();
		table->insert("window-max-size-x", windowMaxSize.x);
		table->insert("window-max-size-y", windowMaxSize.y);
		table->insert("fullscreen", fullscreen);
		root->insert("display", table);
	}

	void load(std::shared_ptr<cpptoml::table> root)
	{
		const auto table = root->get_table("display");
		if (table == nullptr) // "display" section does not exist.
			return;
		//
		windowMaxSize.x = table->get_as<uint32_t>("window-max-size-x").value_or(1920);
		windowMaxSize.y = table->get_as<uint32_t>("window-max-size-y").value_or(1016);
		fullscreen = table->get_as<bool>("fullscreen").value_or(false);
	}

};

#endif // T1_DISPLAY_SETTINGS_H
