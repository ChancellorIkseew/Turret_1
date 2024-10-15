#pragma once
#ifndef MAIN_CONTROL_PANEL_H
#define MAIN_CONTROL_PANEL_H

#include <map>

#include "game_interface/sub_window/sub_window/sub_window.h"
#include "game_interface/sub_window/elements/button/button.h"


class MainControlPanel : public SubWindow
{
private:
	bool isPaused;
	
	std::map<int, Button> buttons;
	
	sf::Text waveNumberText;
	sf::Text waveNumberText2;
	sf::Text waveTimerText;
	sf::Text waveTimerText2;

	MainControlPanel();
	MainControlPanel(const MainControlPanel&) = delete;
	MainControlPanel& operator=(const MainControlPanel&) = delete;
	~MainControlPanel() = default;
	
public:
	
	static MainControlPanel& getInstance()
	{
		static MainControlPanel self;
		return self;
	}
	
	void interact(sf::Vector2i& mouseCoord, bool& isPaused, bool& isGameplayActive, const std::string& saveFolderName);
	void interactWaveTimer(const bool isPaused);

	void prepareInterfaceSprites() override final;
	void draw(sf::RenderWindow& window) override final;
	
};

#endif // MAIN_CONTROL_PANEL_H
