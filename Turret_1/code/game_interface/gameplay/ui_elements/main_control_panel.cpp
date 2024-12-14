
#include <iostream>
#include <sstream>
#include <string>

#include "main_control_panel.h"

#include "game_interface/ui_window/sub_win_util/fonts.h"

#include "settings_window.h"
#include "exit_confirmation.h"

#include "game_interface/gameplay/gameplay_util/t1_time.h"

#include "map_structures/terrain/terrain.h"
#include "map_structures/buildings/buildings_map/buildings_map.h"
#include "map_structures/particles/particles.h"
#include "map_structures/pre-settings/pre-settings.h"
#include "t1_system/t1_mutex.h"

enum buttonsEnum
{
	SAVE = 0,
	HELP = 1,
	EXIT_TO_MENU = 2,
	SETTINGS = 3,
	SET_PAUSE = 4,
	REMOVE_PAUSE = 5
};

MainControlPanel::MainControlPanel() : UIWindow(sf::Vector2u(312, 110), sf::Vector2u(0, 0))
{
	isPaused = true;
	this->prepareInterfaceSprites();
}


void MainControlPanel::prepareInterfaceSprites()
{
	buttons[SAVE] = Button("save.bmp", sf::Vector2i(48, 48), sf::Vector2i(130, 10));
	buttons[HELP] = Button("help.bmp", sf::Vector2i(48, 48), sf::Vector2i(190, 10));
	buttons[EXIT_TO_MENU] = Button("exit_to_menu.bmp", sf::Vector2i(48, 48), sf::Vector2i(70, 10));
	buttons[SETTINGS] = Button("settings.bmp", sf::Vector2i(48, 48), sf::Vector2i(10, 10));
	buttons[SET_PAUSE] = Button("set_pause.bmp", sf::Vector2i(48, 48), sf::Vector2i(250, 10));
	buttons[REMOVE_PAUSE] = Button("remove_pause.bmp", sf::Vector2i(48, 48), sf::Vector2i(250, 10));

	for (auto& btn : buttons)
	{
		btn.second.relocateWithOwner(position);
	}

	waveNumberText = sf::Text(sf::String(L"волна: "), turretClassic, 16);
	waveNumberText.setFillColor(standardColor);
	waveNumberText.setPosition(10, 60);

	waveNumberText2 = sf::Text(sf::String(L" "), turretClassic, 16);
	waveNumberText2.setFillColor(standardColor);
	waveNumberText2.setPosition(65, 60);
	

    waveTimerText = sf::Text(sf::String(L"до следующей волны: "), turretClassic, 16);
    waveTimerText.setFillColor(standardColor);
	waveTimerText.setPosition(10, 80);
	
	waveTimerText2 = sf::Text(sf::String(L" "), turretClassic, 16);
    waveTimerText2.setFillColor(standardColor);
	waveTimerText2.setPosition(200, 80);
}



void MainControlPanel::interact(bool& isPaused, bool& isGameplayActive)
{
	if (buttons[SAVE].press())
	{
		PreSettings::savePreSettings();

		std::lock_guard<std::mutex> guard(t1::system::mt::buildings);
		//TerrainMap::saveMap(saveFolderName);
		//BuildingsMap::saveMap(saveFolderName);
		//t1::time::saveTime(saveFolderName);
	}
	
	if (buttons[EXIT_TO_MENU].press())
	{
		ConfirmationWindow::getInstance().setVisible(true);
		
		if(ConfirmationWindow::getInstance().interact())
		{
			std::lock_guard<std::mutex> guard(t1::system::mt::buildings);
			cleanParticlesList();
			isGameplayActive = false;
		}
		
		ConfirmationWindow::getInstance().setVisible(false);
	}
	
	if (buttons[SETTINGS].press())
	{
		//SettingsWindow::getInstance().setVisible(true);
		//SettingsWindow::getInstance().interact(mouseCoord);
		//SettingsWindow::getInstance().setVisible(false);
	}
	
	if (buttons[HELP].press())
	{
		std::cout << "help button works" << std::endl;
	}
	
	if (buttons[SET_PAUSE].press())
	{
		std::cout << "set pause button works" << std::endl;
		isPaused = true;
		this->isPaused = isPaused;
		buttons[SET_PAUSE].setVisible(false);
		buttons[REMOVE_PAUSE].setVisible(true);
	}
	
	if (buttons[REMOVE_PAUSE].press())
	{
		std::cout << "remove pause button works" << std::endl;
		isPaused = false;
		this->isPaused = isPaused;
		buttons[REMOVE_PAUSE].setVisible(false);
		buttons[SET_PAUSE].setVisible(true);
	}
	
}



void MainControlPanel::interactWaveTimer(const bool isPaused)
{
	if(!isPaused)
	{
		std::ostringstream strWaveNumber;
		strWaveNumber << t1::time::waveNumber;
		waveNumberText2.setString(strWaveNumber.str());

    	std::ostringstream strSeconds;
		strSeconds << (59 - ((t1::time::time / 60) % 60));

    	std::ostringstream strMinutes;
		strMinutes << int(2 - (t1::time::time / 3600));

    	waveTimerText2.setString(strMinutes.str() + " : " + strSeconds.str());
	}
}



void MainControlPanel::draw(sf::RenderWindow& window)
{
	drawBase(window);
	for (auto& btn : buttons)
	{
		btn.second.draw(window);
	}
    
	window.draw(waveNumberText);
	window.draw(waveNumberText2);

    window.draw(waveTimerText);
    window.draw(waveTimerText2);
}
