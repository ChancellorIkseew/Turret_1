#pragma once
#ifndef T1_DISPLAY_SETTINGS_H
#define T1_DISPLAY_SETTINGS_H

#include <SFML/Graphics.hpp>
#include "util/parser/cpptoml.h"

struct DisplaySettings
{
	sf::Vector2u windowMaxSize = sf::Vector2u(1920, 1016);

	void save(std::shared_ptr<cpptoml::table> root) const
	{
		auto table = cpptoml::make_table();
		table->insert("window-max-size-x", windowMaxSize.x);
		table->insert("window-max-size-y", windowMaxSize.y);
		root->insert("display", table);
	}

	void load(std::shared_ptr<cpptoml::table> root)
	{
		const auto table = root->get_table("display");
		//
		windowMaxSize.x = table->get_as<double>("window-max-size-x").value_or(1920);
		windowMaxSize.y = table->get_as<double>("window-max-size-y").value_or(1016);
	}

};

#endif // T1_DISPLAY_SETTINGS_H
