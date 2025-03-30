
#include "settings.h"
#include <iostream>
#include <fstream>
#include <cpptoml.h>
#include <filesystem>

static const std::filesystem::path settings("settings/settings");

void Settings::save()
{
	std::ofstream fout;
	fout.open(settings);
	if (!fout.is_open())
		throw std::runtime_error("Unable to open file to write: saves/settings.toml"); // Should not be catched. (crash the game)
	auto root = cpptoml::make_table();
	audio.save(root);
	display.save(root);
	gui.save(root);
	saving.save(root);
	cpptoml::toml_writer writer(fout, " ");
	writer.visit(*root, false);
	fout.close();
}

void Settings::load()
{
	try
	{
		const auto root = cpptoml::parse_file(settings.string());
		audio.load(root);
		display.load(root);
		gui.load(root);
		saving.load(root);
	}
	catch (cpptoml::parse_exception) // If settings file does not exist.
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
