
#include "load_game_menu.h"

#include "map_structures/pre-settings/pre-settings.h"
#include "game_interface/ui_window/sub_win_util/fonts.h"
#include "t1_system/input/input_handler.h"
#include "t1_system/sleep.h"

enum buttonsEnum
{
	LOAD_GAME = 0,
	SAVE = 1,
	EXIT_TO_MENU = 2,
};

LoadGameMenu::LoadGameMenu() : UIWindow(sf::Vector2i(720, 480))
{
	this->prepareInterfaceSprites();
	isVisible = false;
	folderSelected = false;
}


void LoadGameMenu::prepareInterfaceSprites()
{
	buttons[EXIT_TO_MENU] = Button("exit.bmp", sf::Vector2i(48, 48), sf::Vector2i(10, 10));
	buttons[LOAD_GAME] = Button("load_game.bmp", sf::Vector2i(364, 48), sf::Vector2i(68, 10));
	buttons[SAVE] = Button("save.bmp", sf::Vector2i(48, 48), sf::Vector2i(68, 10));
	newFolder = TextField(sf::String(""), 170, sf::Vector2i(126, 10));

	namespace stdfs = std::filesystem;
	int i = 0;
	for (const auto& entry : stdfs::directory_iterator("saves"))
		if (stdfs::is_directory(entry))
		{
			saves[i] = SaveUI(entry.path().filename().string(), sf::Vector2i(0, 0));
			++i;
		}
}


GameState LoadGameMenu::interact(bool& isMenuOpen, std::string& saveFolderName, const SavesAction action)
{
	if (action == SavesAction::LOAD)
		buttons[SAVE].setVisible(false);
	else
		buttons[LOAD_GAME].setVisible(false);

	while (isMenuOpen && !InputHandler::active(t1::BindName::Escape))
	{
		if ((buttons[LOAD_GAME].press() || buttons[SAVE].press()) && folderSelected)
			return GameState::GAMEPLAY;	
		if (buttons[EXIT_TO_MENU].press())
			break;
		for (auto& [_, save] : saves)
			if (save.press())
			{
				saveFolderName = save.getFolder();
				folderSelected = true;
			}
		if (action == SavesAction::SAVE)
		{
			newFolder.interact();
			std::string str = newFolder.getValueSTDString();
			if (str.empty())
				continue;
			saveFolderName = str;
			folderSelected = true;
		}

		t1::system::sleep(16);
	}
	return GameState::MAIN_MENU;
}


void LoadGameMenu::relocate(const sf::Vector2i windowSize)
{
	relocateCentral(windowSize);
	for (auto& [_, btn] : buttons)
		btn.relocateWithOwner(position);
	newFolder.relocateWithOwner(position);
}


void LoadGameMenu::draw(sf::RenderWindow& window)
{
	if (!isVisible)
		return;
	drawBase(window);
	newFolder.draw(window);
	for (auto& [_, btn] : buttons)
		btn.draw(window);
	int posX = position.x + 10;
	int posY = position.y + 68;
	for (auto& [_, save] : saves)
	{
		save.draw(window, posX, posY);
		posY += 60;
	}
}
