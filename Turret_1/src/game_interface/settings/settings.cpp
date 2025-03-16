
#include <iostream>
#include <fstream>
#include <cpptoml.h>

#include "settings.h"


void Settings::save()
{
	std::ofstream fout;
	fout.open("saves/settings.toml");
	if (!fout.is_open())
		throw std::runtime_error("Unable to open file to write: saves/settings.toml"); // Should not be catched. (crash the game)
	cpptoml::toml_writer writer(fout, " ");
	auto root = cpptoml::make_table();
	display.save(root);
	gui.save(root);
	saving.save(root);
	writer.visit(*root, false);
	fout.close();
}

void Settings::load()
{
	try
	{
		const auto root = std::move(cpptoml::parse_file("saves/settings.toml"));
		display.load(root);
		gui.load(root);
		saving.load(root);
	}
	catch (cpptoml::parse_exception) // Settings file does not exist.
	{
		std::cout << "Settings file not found. Default settings applied.\n";
		save();
	}
}

// If the settings file does not exist, it will be generated automatically with the default settings.
// If one section of the settings does not exist in the file, the default settings will be applied to this section.
// If there is no specific item inside the section, the default settings will be applied to this item.
// 
// The next time you save the settings, the sections and individual items to which the default settings
// have been applied will be written to the settings file.
