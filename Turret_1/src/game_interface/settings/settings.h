#pragma once
#ifndef TURRET_1_SETTINGS_H
#define TURRET_1_SETTINGS_H

#include "settings/audio.h"
#include "settings/display_settings.h"
#include "settings/gui_settings.h"
#include "settings/saving_settings.h"

class Settings
{
private:
	static inline AudioSettings audio;
	static inline DisplaySettings display;
	static inline GuiSettings gui;
	static inline SavingSettings saving;

public:
	static void save();
	static void load();

	static AudioSettings& getAudio() { return audio; }
	static DisplaySettings& getDisplay() { return display; }
	static GuiSettings& getGui() { return gui; }
	static SavingSettings& getSaving() { return saving; }
	static void getGraphics() { }

};

#endif // SETTINGS_SAVE_SYSTEM_H
