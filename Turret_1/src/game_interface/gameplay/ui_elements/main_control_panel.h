#pragma once
#ifndef MAIN_CONTROL_PANEL_H
#define MAIN_CONTROL_PANEL_H

#include <map>

#include "game_interface/ui_window/ui_window/ui_window.h"
#include "game_interface/ui_window/elements/button/button.h"

class World;

class MainControlPanel : public UIWindow
{
private:
	std::map<int, Button> buttons;
	
	sf::Text waveNumberText;
	sf::Text waveNumberText2;
	sf::Text waveTimerText;
	sf::Text waveTimerText2;
	
	MainControlPanel(const MainControlPanel&) = delete;
	MainControlPanel& operator=(const MainControlPanel&) = delete;
	
public:
	MainControlPanel();
	~MainControlPanel() = default;
	
	void interact(bool& isPaused, bool& isGameplayActive, std::atomic_int& tickSpeed, const World& world);
	void interactWaveTimer(const bool isPaused, const World& world);

	void prepareInterfaceSprites() override final;
	void draw(sf::RenderWindow& window) override final;
	
};

#endif // MAIN_CONTROL_PANEL_H
