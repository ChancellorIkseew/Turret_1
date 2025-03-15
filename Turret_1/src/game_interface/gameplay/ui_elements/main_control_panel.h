#pragma once
#ifndef MAIN_CONTROL_PANEL_H
#define MAIN_CONTROL_PANEL_H

#include <map>

#include "game_interface/ui_window/ui_window/ui_window.h"
#include "game_interface/ui_window/elements/button/button.h"
#include "exit_confirmation.h"

class World;

class MainControlPanel : public UIWindow
{
private:
	std::map<int, Button> buttons;
	
	sf::Text waveNumberText = sf::Text(turretClassic);
	sf::Text waveNumberText2 = sf::Text(turretClassic);
	sf::Text waveTimerText = sf::Text(turretClassic);
	sf::Text waveTimerText2 = sf::Text(turretClassic);

	std::unique_ptr<ConfirmationWindow> confirmationWindow;
	
	MainControlPanel(const MainControlPanel&) = delete;
	MainControlPanel& operator=(const MainControlPanel&) = delete;
	void prepareInterfaceSprites() override final;
	
public:
	MainControlPanel();
	~MainControlPanel() = default;
	
	void interact(bool& isPaused, bool& isGameplayActive, std::atomic_int& tickSpeed, const World& world);
	void interactWaveTimer(const bool isPaused, const World& world);
	void relocate(const sf::Vector2i windowSize) override final;

	void draw(sf::RenderWindow& window) override final;
	
};

#endif // MAIN_CONTROL_PANEL_H
