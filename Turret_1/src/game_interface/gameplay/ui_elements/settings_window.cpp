
#include "settings_window.h"

#include "game_interface/ui_window/sub_win_util/fonts.h"
#include "game_interface/sound_system/sound_system.h"
#include "game_interface/settings/settings.h"
#include "t1_system/input/input_handler.h"
#include "t1_system/sleep.h"
#include "content/texturepacks.h"

enum fieldEnum
{
	WINDOW_SIZE_X = 0,
	WINDOW_SIZE_Y = 1,
	FULLSCREEN = 2,
	SHOW_MINIMAP = 3,
	MUSIC = 4,
	SOUNDS = 5,
	NEED_RESTART = 6
};

SettingsWindow::SettingsWindow() : UIWindow(sf::Vector2i(720, 480))
{
	this->prepareInterfaceSprites();
	isVisible = false;
}


void SettingsWindow::prepareInterfaceSprites()
{
	exit = Button("exit.bmp", sf::Vector2i(48, 48), sf::Vector2i(10, 10));
	confirm = Button("confirm.bmp", sf::Vector2i(48, 48), sf::Vector2i(70, 10));
	update = Button("update.bmp", sf::Vector2i(48, 48), sf::Vector2i(662, 10));

	const int line0 = 10;
	labels[WINDOW_SIZE_X] = Label(L"Разрешение\nэкрана", sf::Vector2i(line0, 80));
	labels[FULLSCREEN] = Label(L"Полноэкранный\nрежим", sf::Vector2i(line0, 125));
	labels[SHOW_MINIMAP] = Label(L"Отображать\nминикарту", sf::Vector2i(line0, 155));
	labels[MUSIC] = Label(L"Громкость\nмузыки", sf::Vector2i(line0, 185));
	labels[SOUNDS] = Label(L"Громкось\nзвуков", sf::Vector2i(line0, 215));
	labels[NEED_RESTART] = Label(L"Применяется после\nперезапуска игры", sf::Vector2i(140, 125));

	const int line1 = 110;
	fields[WINDOW_SIZE_X] = TextField(Settings::getDisplay().windowMaxSize.x, 42, sf::Vector2i(line1, 70));
	fields[WINDOW_SIZE_Y] = TextField(Settings::getDisplay().windowMaxSize.y, 42, sf::Vector2i(line1, 95));
	fields[MUSIC] = TextField(Settings::getAudio().music, 42, sf::Vector2i(line1, 185));
	fields[SOUNDS] = TextField(Settings::getAudio().sounds, 42, sf::Vector2i(line1, 215));

	fullscreen = Checkbox(Settings::getDisplay().fullscreen, sf::Vector2i(line1, 125));
	showMinimap = Checkbox(Settings::getGui().showMinimap, sf::Vector2i(line1, 155));
}

void SettingsWindow::aply()
{
	Settings::getDisplay().windowMaxSize = sf::Vector2u(fields[WINDOW_SIZE_X].getValueUint32(), fields[WINDOW_SIZE_Y].getValueUint32());
	Settings::getDisplay().fullscreen = fullscreen.getValue();
	Settings::getGui().showMinimap = showMinimap.getValue();
	Settings::getAudio().music = fields[MUSIC].getValueUint32();
	Settings::getAudio().sounds = fields[SOUNDS].getValueUint32();
	Settings::save();
	SoundSystem::setVolumeBySettings();
	//Texturepacks::saveConfig();
	//Texturepacks::loadTextures();
}

void SettingsWindow::interact(const bool& windowOpen)
{
	while (windowOpen && !InputHandler::active(t1::BindName::Escape))
	{
		if (exit.press())
			return;
		if (confirm.press())
			aply();
		if (update.press())
		{
			Texturepacks::loadConfig();
			Texturepacks::loadTextures();
		}
		fullscreen.press();
		showMinimap.press();
		for (auto& [_, field] : fields)
			field.interact();
		t1::system::sleep(16);
	}
}


void SettingsWindow::relocate(const sf::Vector2i windowSize)
{
	relocateCentral(windowSize);
	exit.relocateWithOwner(position);
	confirm.relocateWithOwner(position);
	update.relocateWithOwner(position);
	fullscreen.relocateWithOwner(position);
	showMinimap.relocateWithOwner(position);
	for (auto& [_, label] : labels)
		label.relocateWithOwner(position);
	for (auto& [_, field] : fields)
		field.relocateWithOwner(position);
}


void SettingsWindow::draw(sf::RenderWindow& window)
{
	if (!isVisible)
		return;
	drawBase(window);
	exit.draw(window);
	confirm.draw(window);
	update.draw(window);
	fullscreen.draw(window);
	showMinimap.draw(window);
	for (const auto& [_, label] : labels)
		label.draw(window);
	for (auto& [_, field] : fields)
		field.draw(window);
}
