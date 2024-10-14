#pragma once
#ifndef PRE1
#define PRE1

#include <map>
#include <vector>
#include <SFML/Graphics.hpp>

#include "game_interface/gameplay/sub_windows/sub_windows_util/sub_window.h"
#include "game_interface/gameplay/sub_windows/sub_windows_util/page/page.h"
#include "game_interface/gameplay/sub_windows/sub_windows_util/button/button.h"


class PreSettingsWindow : public SubWindow
{
private:
	std::vector<Button> buttons;
	std::map<int, std::unique_ptr<Page>> pages;

public:
	PreSettingsWindow();
	~PreSettingsWindow() = default;

	int interact(sf::Vector2i& mouseCoord, bool& isMenuOpen);
	void relocate(sf::Vector2u windowSize) override final;

	void prepareInterfaceSprites() override final;
	void draw(sf::RenderWindow& window) override final;

};

#endif // !PRE1
