
#include <iostream>
#include <fstream>
#include "util/parser/cpptoml.h"

#include "settings.h"


void Settings::save()
{
	std::ofstream fout;
	fout.open("saves/global_settings.toml");
	if (!fout.is_open())
		throw std::runtime_error("Unable to open file to write: saves/settings.toml");
	auto root = cpptoml::make_table();
	display.save(root);
	fout.close();
}

void Settings::load()
{
	try
	{
		const auto root = std::move(cpptoml::parse_file("saves/settings.toml"));
		display.load(root);
	}
	catch (std::runtime_error)
	{
		std::cout << "Settings file not found. Default settings applied.\n";
	}
}
