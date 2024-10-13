
#include <iostream>
#include <sstream>
#include <string>
#include <SFML\Graphics.hpp>


#include "main_control_panel.h"

#include "sub_windows_util/sub_windows_list.h"
#include "sub_windows_util/fonts.h"


#include "settings_window.h"
#include "exit_confirmation.h"

#include "game_interface/gameplay/gameplay_util/t1_time.h"
#include "game_interface/gameplay/gameplay_util/wave_constructor.h"

#include "map_structures/terrain/terrain.h"
#include "map_structures/buildings/buildings_map/buildings_map.h"
#include "map_structures/particles/particles.h"
#include "map_structures/resources/resources.h"
#include "map_structures/resources/resource_units.h"
#include "map_structures/pre-settings/pre-settings.h"
#include "map_structures/base_engine/t1_mutex.h"


MainControlPanel::MainControlPanel() : SubWindow('s', 312, 110, 0, 0)
{
	isPaused = true;
	this->prepareInterfaceSprites();
}


void MainControlPanel::prepareInterfaceSprites()
{
	save = Button("save.bmp", sf::Vector2i(48, 48), sf::Vector2i(130, 10));
	help = Button("help.bmp", sf::Vector2i(48, 48), sf::Vector2i(190, 10));
	exitToMenu = Button("exit_to_menu.bmp", sf::Vector2i(48, 48), sf::Vector2i(70, 10));
	settings = Button("settings.bmp", sf::Vector2i(48, 48), sf::Vector2i(10, 10));
	setPause = Button("set_pause.bmp", sf::Vector2i(48, 48), sf::Vector2i(250, 10));
	removePause = Button("remove_pause.bmp", sf::Vector2i(48, 48), sf::Vector2i(250, 10));

	save.relocate(sf::Vector2i(positionX, positionY));
	help.relocate(sf::Vector2i(positionX, positionY));
	exitToMenu.relocate(sf::Vector2i(positionX, positionY));
	settings.relocate(sf::Vector2i(positionX, positionY));
	setPause.relocate(sf::Vector2i(positionX, positionY));
	removePause.relocate(sf::Vector2i(positionX, positionY));
	

	waveNumberText.setFont(turretClassic);											//Text_wave_number
	waveNumberText.setString(sf::String(L"волна: "));
	waveNumberText.setPosition(10, 60);
	waveNumberText.setCharacterSize(16);
	waveNumberText.setFillColor(sf::Color(68, 52, 52));

	waveNumberText2.setFont(turretClassic);
	waveNumberText2.setPosition(65, 60);
	waveNumberText2.setCharacterSize(16);
	waveNumberText2.setFillColor(sf::Color(68, 52, 52));

    waveTimerText.setFont(turretClassic);											//Text_wave_timer
    waveTimerText.setString(sf::String(L"до следующей волны: "));
    waveTimerText.setPosition(10, 80);
    waveTimerText.setCharacterSize(16);
    waveTimerText.setFillColor(sf::Color(68, 52, 52));
	
    waveTimerText2.setFont(turretClassic);					//Text_wave_timer_time
    waveTimerText2.setPosition(200, 80);
    waveTimerText2.setCharacterSize(16);
    waveTimerText2.setFillColor(sf::Color(68, 52, 52));	
}



void MainControlPanel::interact(sf::Vector2i& mouseCoord, bool& isPaused, bool& isGameplayActive, const std::string& saveFolderName)
{
	if (save.press(mouseCoord))
	{
		PreSettings::savePreSettings();

		mtBuildings.lock();
		TerrainMap::saveMap(saveFolderName);
		BuildingsMap::saveMap(saveFolderName);
		//saveEntitiesList(saveFolderName);
		//saveResUnitsList(saveFolderName);
		t1::time::saveTime(saveFolderName);
		//t1::res::saveResources(saveFolderName);
		mtBuildings.unlock();
	}
	
	if (exitToMenu.press(mouseCoord))
	{
		ConfirmationWindow::getInstance().setVisible(true);
		
		if(ConfirmationWindow::getInstance().interact(mouseCoord))
		{
			mtBuildings.lock();
			cleanParticlesList();
			cleanResUnitsList();
			mtBuildings.unlock();
			
			isGameplayActive = false;
		}
		
		ConfirmationWindow::getInstance().setVisible(false);
	}
	
	if (settings.press(mouseCoord))
	{
		SettingsWindow::getInstance().setVisible(true);
		SettingsWindow::getInstance().interact(mouseCoord);
		SettingsWindow::getInstance().setVisible(false);
	}
	
	if (help.press(mouseCoord))
	{
		std::cout << "help button works" << std::endl;
	}
	
	if (setPause.press(mouseCoord))
	{
		std::cout << "set pause button works" << std::endl;
		isPaused = true;
		this->isPaused = isPaused;
		setPause.setVisible(false);
		removePause.setVisible(true);
	}
	
	if (removePause.press(mouseCoord))
	{
		std::cout << "remove pause button works" << std::endl;
		isPaused = false;
		this->isPaused = isPaused;
		removePause.setVisible(false);
		setPause.setVisible(true);
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
	this->drawSubWindowBase(window);
    
    settings.draw(window);
	exitToMenu.draw(window);
    save.draw(window);
    help.draw(window);
	setPause.draw(window);
	removePause.draw(window);
    
	window.draw(waveNumberText);
	window.draw(waveNumberText2);

    window.draw(waveTimerText);
    window.draw(waveTimerText2);
}
