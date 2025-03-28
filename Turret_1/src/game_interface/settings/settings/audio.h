#pragma once
#ifndef T1_AUDIO_SETTINGS_H
#define T1_AUDIO_SETTINGS_H

#include <cpptoml.h>

struct AudioSettings
{
	uint8_t music = 5;
	uint8_t sounds = 20;

	void save(std::shared_ptr<cpptoml::table> root) const
	{
		auto table = cpptoml::make_table();
		table->insert("music", music);
		table->insert("sounds", sounds);
		root->insert("audio", table);
	}

	void load(std::shared_ptr<cpptoml::table> root)
	{
		const auto table = root->get_table("audio");
		if (table == nullptr) // "audio" section does not exist.
			return;
		//
		music = table->get_as<uint8_t>("music").value_or(5);
		sounds = table->get_as<uint8_t>("window-max-size-y").value_or(20);
	}

};

#endif // T1_AUDIO_SETTINGS_H
