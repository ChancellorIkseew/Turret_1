
#include "load_game_menu.h"

#include "map_structures/pre-settings/pre-settings.h"
#include "game_interface/ui_window/sub_win_util/fonts.h"
#include "t1_system/input/input_handler.h"
#include "t1_system/sleep.h"

enum buttonsEnum
{
	LOAD_GAME = 0,
	EXIT_TO_MENU = 1,
};

LoadGameMenu::LoadGameMenu() : UIWindow(sf::Vector2i(720, 480))
{
	this->prepareInterfaceSprites();
	isVisible = false;
	folderSelected = false;
}


void LoadGameMenu::prepareInterfaceSprites()
{
	buttons[LOAD_GAME] = Button("load_game.bmp", sf::Vector2i(364, 48), sf::Vector2i(10, 68));
	buttons[EXIT_TO_MENU] = Button("exit_to_menu.bmp", sf::Vector2i(48, 48), sf::Vector2i(10, 10));

	helpText.setCharacterSize(16);
	helpText.setString(sf::String(L"„тобы начать игру, нужно выбрать сохранение,\nв которое будет записыватьс€ игровой прогресс."));
	helpText.setFillColor(darkRed);

	namespace stdfs = std::filesystem;
	int i;
	for (const auto& entry : stdfs::directory_iterator("saves"))
		if (stdfs::is_directory(entry))
		{
			saves[i] = SaveUI(entry.path().filename().string(), sf::Vector2i(0, 0));
			++i;
		}
}


GameState LoadGameMenu::interact(bool& isMenuOpen, std::string& saveFolderName)
{
	while (isMenuOpen && !InputHandler::active(t1::BindName::Escape))
	{
		if (buttons[LOAD_GAME].press() && folderSelected)
			return GameState::GAMEPLAY;	
		if (buttons[EXIT_TO_MENU].press())
			break;

		for (auto& [_, save] : saves)
			if (save.press())
			{
				saveFolderName = save.getFolder();
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

	helpText.setPosition(sf::Vector2f(position.x + 70, position.y + 350));
}


void LoadGameMenu::draw(sf::RenderWindow& window)
{
	if (!isVisible)
		return;
	drawBase(window);
	for (auto& [_, btn] : buttons)
		btn.draw(window);
	if (!folderSelected)
		window.draw(helpText);
	int posX = position.x + 10;
	int posY = position.y + 126;
	for (auto& [_, save] : saves)
	{
		save.draw(window, posX, posY);
		posY += 60;
	}
}
