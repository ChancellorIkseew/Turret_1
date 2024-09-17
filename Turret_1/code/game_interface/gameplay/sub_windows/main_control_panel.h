#pragma once
#ifndef MAIN_CONTROL_PANEL_H
#define MAIN_CONTROL_PANEL_H

#include <SFML\Graphics.hpp>

#include "sub_windows_util/sub_window.h"


class MainControlPanel : public SubWindow
{
private:

	bool isPaused;
	
	sf::Image saveButtonImage;
	sf::Texture saveButtonTexture;
	sf::Sprite saveButtonSprite;
	
	sf::Image helpButtonImage;
	sf::Texture helpButtonTexture;
	sf::Sprite helpButtonSprite;
	
	sf::Image etmButtonImage;
	sf::Texture etmButtonTexture;
	sf::Sprite etmButtonSprite;
	
	sf::Image settingButtonImage;
	sf::Texture settingButtonTexture;
	sf::Sprite settingButtonSprite;
	
	sf::Image remPauseButtonImage;
	sf::Texture remPauseButtonTexture;
	sf::Sprite remPauseButtonSprite;
	
	sf::Image setPauseButtonImage;
	sf::Texture setPauseButtonTexture;
	sf::Sprite setPauseButtonSprite;
	
	sf::Text waveNumberText;
	sf::Text waveNumberText2;

	sf::Text waveTimerText;
	sf::Text waveTimerText2;
	
public:
	
	MainControlPanel();
	~MainControlPanel() = default;
	
	void prepareInterfaceSprites() override;
	
	void interact(sf::Vector2i& mouseCoord, int time, bool& isPaused, bool& isGameplayActive, std::string saveFolderName);
	
	void interactWaveTimer(int time, bool isPaused);
	
	void draw(sf::RenderWindow& window) override;
	
};


#endif // MAIN_CONTROL_PANEL_H
