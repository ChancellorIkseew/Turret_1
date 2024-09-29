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
