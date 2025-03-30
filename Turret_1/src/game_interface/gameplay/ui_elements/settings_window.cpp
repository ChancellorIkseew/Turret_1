
#include "settings_window.h"

#include "game_interface/ui_window/sub_win_util/fonts.h"
#include "game_interface/sound_system/sound_system.h"
#include "game_interface/settings/settings.h"
#include "game_interface/main_window/main_window_resize.h"
#include "t1_system/input/input_handler.h"
#include "t1_system/sleep.h"
#include "content/texturepacks.h"

enum fieldEnum
{
	WINDOW_SIZE_X = 0,
	WINDOW_SIZE_Y = 1,
	SHOW_MINIMAP = 2,
	MUSIC = 3,
	SOUNDS = 4
};

SettingsWindow::SettingsWindow() : UIWindow(sf::Vector2i(720, 480))
{
	this->prepareInterfaceSprites();
	isVisible = false;
}


void SettingsWindow::prepareInterfaceSprites()
{
	exit = Button("exit_to_menu.bmp", sf::Vector2i(48, 48), sf::Vector2i(10, 10));
	confirm = Button("confirm.bmp", sf::Vector2i(48, 48), sf::Vector2i(70, 10));

	const int line0 = 110;
	fields[WINDOW_SIZE_X] = TextField(Settings::getDisplay().windowMaxSize.x, 42, sf::Vector2i(line0, 70));
	fields[WINDOW_SIZE_Y] = TextField(Settings::getDisplay().windowMaxSize.y, 42, sf::Vector2i(line0, 95));
	fields[SHOW_MINIMAP] = TextField(static_cast<uint32_t>(Settings::getGui().showMinimap), 42, sf::Vector2i(line0, 125));
	fields[MUSIC] = TextField(Settings::getAudio().music, 42, sf::Vector2i(line0, 155));
	fields[SOUNDS] = TextField(Settings::getAudio().sounds, 42, sf::Vector2i(line0, 185));
	tResolution = sf::Text(turretClassic, sf::String(L"Разрешение\nэкрана"), 12);
	tMinimap = sf::Text(turretClassic, sf::String(L"Отображать\nминикарту"), 12);
	tMusic = sf::Text(turretClassic, sf::String(L"Громкость\nмузыки"), 12);
	tSounds = sf::Text(turretClassic, sf::String(L"Громкось\nзвуков"), 12);
	tResolution.setFillColor(standardColor);
	tMinimap.setFillColor(standardColor);
	tMusic.setFillColor(standardColor);
	tSounds.setFillColor(standardColor);
}

void SettingsWindow::aply()
{
	Settings::getDisplay().windowMaxSize = sf::Vector2u(fields[WINDOW_SIZE_X].getValueUint32(), fields[WINDOW_SIZE_Y].getValueUint32());
	Settings::getGui().showMinimap = fields[SHOW_MINIMAP].getValueUint32() != 0;
	Settings::getAudio().music = fields[MUSIC].getValueUint32();
	Settings::getAudio().sounds = fields[SOUNDS].getValueUint32();
	Settings::save();
	Texturepacks::saveConfig();
	SoundSystem::setVolumeBySettings();
}

void SettingsWindow::interact(const bool& windowOpen)
{
	while (windowOpen)
	{
		if (exit.press())
			return;
		if (confirm.press())
			aply();
		for (auto& field : fields)
			field.second.interact();
		t1::system::sleep(16);
	}
}


void SettingsWindow::relocate(const sf::Vector2i windowSize)
{
	relocateCentral(windowSize);
	exit.relocateWithOwner(position);
	confirm.relocateWithOwner(position);
	tResolution.setPosition(sf::Vector2f(position.x + 10, position.y + 80));
	tMinimap.setPosition(sf::Vector2f(position.x + 10, position.y + 125));
	tMusic.setPosition(sf::Vector2f(position.x + 10, position.y + 155));
	tSounds.setPosition(sf::Vector2f(position.x + 10, position.y + 185));
	for (auto& field : fields)
		field.second.relocateWithOwner(position);
}


void SettingsWindow::draw(sf::RenderWindow& window)
{
	if (!isVisible)
		return;
	drawBase(window);
	exit.draw(window);
	confirm.draw(window);
	window.draw(tResolution);
	window.draw(tMinimap);
	window.draw(tMusic);
	window.draw(tSounds);
	for (auto& field : fields)
		field.second.draw(window);
}
