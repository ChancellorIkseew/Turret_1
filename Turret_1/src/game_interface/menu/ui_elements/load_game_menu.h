#pragma once
#ifndef CHOISE_FOLDER_MENU_H
#define CHOISE_FOLDER_MENU_H

#include <map>
#include <unordered_set>

#include "game_interface/main_window/game_state.h"
#include "game_interface/ui_window/ui_window/ui_window.h"
#include "game_interface/ui_window/sub_win_types/text_field/text_field.h"
#include "game_interface/ui_window/elements/save_ui/save_ui.h"
#include "game_interface/ui_window/sub_win_util/fonts.h"

enum class SavesAction : uint8_t
{
	SAVE = 0,
	LOAD = 1
};

class LoadGameMenu : public UIWindow
{
private:
	std::map<int, Button> buttons;
	std::map<int, SaveUI> saves;
	TextField newFolder; 
	bool folderSelected;

public:
	LoadGameMenu();
	~LoadGameMenu() = default;

	GameState interact(bool& isMenuOpen, std::string& saveFolderName, const SavesAction action);
	void relocate(sf::Vector2i windowSize) override final;

	void prepareInterfaceSprites() override final;
	void draw(sf::RenderWindow& window) override final;

};


#endif // CHOISE_FOLDER_MENU_H
