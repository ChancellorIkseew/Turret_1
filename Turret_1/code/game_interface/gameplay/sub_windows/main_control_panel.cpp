
#include <iostream>
#include <sstream>
#include <string>
#include <SFML\Graphics.hpp>


#include "main_control_panel.h"

#include "sub_windows_util/sub_windows_list.h"
#include "sub_windows_util/fonts.h"


#include "settings_window.h"
#include "exit_confirmation.h"

#include "../gameplay_util/wave_constructor.h"

#include "../../../map_structures/terrain/terrain.h"
#include "../../../map_structures/buildings/buildings_map.h"

#include "../../../map_structures/entities/entities.h"
#include "../../../map_structures/entities/entities_util/entities_list.h"

#include "../../../map_structures/shells/shells.h"

#include "../../../map_structures/particles/particles.h"

#include "../../../map_structures/resources/resources.h"
#include "../../../map_structures/resources/resource_units.h"

#include "../../../map_structures/pre-settings/pre-settings.h"

#include "../../../map_structures/base_engine/t1_mutex.h"


MainControlPanel::MainControlPanel() : SubWindow('s', 312, 110, 0, 0)
{
	isPaused = true;
	this->prepareInterfaceSprites();
}


void MainControlPanel::prepareInterfaceSprites()
{
	saveButtonImage.loadFromFile("images/buttons/save.bmp");						//Button_save
	saveButtonTexture.loadFromImage(saveButtonImage);
	saveButtonSprite.setTexture(saveButtonTexture);
	saveButtonSprite.setTextureRect(sf::IntRect(0,0,48,48));
	saveButtonSprite.setPosition(130, 10);
	
	helpButtonImage.loadFromFile("images/buttons/help.bmp");						//Button_help
	helpButtonTexture.loadFromImage(helpButtonImage);
	helpButtonSprite.setTexture(helpButtonTexture);
	helpButtonSprite.setTextureRect(sf::IntRect(0,0,48,48));
	helpButtonSprite.setPosition(190, 10);
	
	etmButtonImage.loadFromFile("images/buttons/exit_to_menu.bmp");				//Button_exit_to_menu
	etmButtonTexture.loadFromImage(etmButtonImage);
	etmButtonSprite.setTexture(etmButtonTexture);
	etmButtonSprite.setTextureRect(sf::IntRect(0,0,48,48));
	etmButtonSprite.setPosition(70, 10);
	
	settingButtonImage.loadFromFile("images/buttons/setting.bmp");				//Button_open_setting
	settingButtonTexture.loadFromImage(settingButtonImage);
	settingButtonSprite.setTexture(settingButtonTexture);
	settingButtonSprite.setTextureRect(sf::IntRect(0,0,48,48));
	settingButtonSprite.setPosition(10, 10);
	
	remPauseButtonImage.loadFromFile("images/buttons/remove_pause.bmp");			//Button_remove_pause
	remPauseButtonTexture.loadFromImage(remPauseButtonImage);
	remPauseButtonSprite.setTexture(remPauseButtonTexture);
	remPauseButtonSprite.setTextureRect(sf::IntRect(0,0,48,48));

	setPauseButtonImage.loadFromFile("images/buttons/set_pause.bmp");			//Button_set_pause
	setPauseButtonTexture.loadFromImage(setPauseButtonImage);
	setPauseButtonSprite.setTexture(setPauseButtonTexture);
	setPauseButtonSprite.setTextureRect(sf::IntRect(0,0,48,48));
	

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



void MainControlPanel::interact(sf::Vector2i& mouseCoord, int time, bool& isPaused, bool& isGameplayActive, std::string saveFolderName)
{
	if (saveButtonSprite.getGlobalBounds().contains(mouseCoord.x, mouseCoord.y))
	{
		std::cout << "save button works" << std::endl;
		
		PreSettings::savePreSettings();

		mtBuildings.lock();
		TerrainMap::saveMap();
		BuildingsMap::saveMap();
		saveEntitiesList(saveFolderName);
		saveResUnitsList(saveFolderName);
		mtBuildings.unlock();

		saveTime(saveFolderName, time);
		saveResources(saveFolderName);
	}
	
	if (etmButtonSprite.getGlobalBounds().contains(mouseCoord.x, mouseCoord.y))
	{
		std::cout << "exit to menu button works" << std::endl;
		ConfirmationWindow::getInstance().setVisible(true);
		
		if(ConfirmationWindow::getInstance().interactWindow(mouseCoord))
		{
			time = 0;
			waveNumber = 0;
			
			mtBuildings.lock();
			cleanEntitiesList();
			cleanShellsList();
			cleanParticlesList();
			cleanResUnitsList();
			mtBuildings.unlock();
			
			isGameplayActive = false;
		}
		
		ConfirmationWindow::getInstance().setVisible(false);
	}
	
	if (settingButtonSprite.getGlobalBounds().contains(mouseCoord.x, mouseCoord.y))
	{
		std::cout << "setting button works" << std::endl;
		SettingsWindow::getInstance().setVisible(true);
		SettingsWindow::getInstance().interact(mouseCoord);
		SettingsWindow::getInstance().setVisible(false);
	}
	
	if (helpButtonSprite.getGlobalBounds().contains(mouseCoord.x, mouseCoord.y))
	{
		std::cout << "help button works" << std::endl;
	}
	
	if (setPauseButtonSprite.getGlobalBounds().contains(mouseCoord.x, mouseCoord.y))
	{
		std::cout << "set pause button works" << std::endl;
		isPaused = true;
		this->isPaused = isPaused;
	}
	
	if (remPauseButtonSprite.getGlobalBounds().contains(mouseCoord.x, mouseCoord.y))
	{
		std::cout << "remove pause button works" << std::endl;
		isPaused = false;
		this->isPaused = isPaused;
	}
	
}



void MainControlPanel::interactWaveTimer(int time, bool isPaused)
{
	if(!isPaused)
	{
		std::ostringstream strWaveNumber;
		strWaveNumber << waveNumber;
		waveNumberText2.setString(strWaveNumber.str());

		//std::cout << time << std::endl;
    	std::ostringstream strSeconds;
		strSeconds << (59 - ((time / 60) % 60));

    	std::ostringstream strMinutes;
		strMinutes << int(2 - (time / 3600));

    	waveTimerText2.setString(strMinutes.str() + " : " + strSeconds.str());
	}
	
}



void MainControlPanel::draw(sf::RenderWindow& window)
{
	this->drawSubWindowBase(window);
    
    window.draw(settingButtonSprite);
    window.draw(etmButtonSprite);
    window.draw(saveButtonSprite);
    window.draw(helpButtonSprite);
    
    if(isPaused)
    {
    	remPauseButtonSprite.setPosition(250, 10);
    	window.draw(remPauseButtonSprite);
    	//std::cout << "pause chek works" << std::endl;
    	setPauseButtonSprite.setPosition(-50, -50);
	}
    else
    {
    	setPauseButtonSprite.setPosition(250, 10);
		window.draw(setPauseButtonSprite);
		
		remPauseButtonSprite.setPosition(-50, -50);
	}
    
	window.draw(waveNumberText);
	window.draw(waveNumberText2);

    window.draw(waveTimerText);
    window.draw(waveTimerText2);
}
