
#include <iostream>
#include <sstream>
#include <string>

#include "main_control_panel.h"

#include "game_interface/ui_window/sub_win_util/fonts.h"

//#include "settings_window.h"


#include "game_interface/gameplay/gameplay_util/t1_time.h"

#include "map_structures/pre-settings/pre-settings.h"
#include "t1_system/input/input_handler.h"
#include "t1_system/t1_mutex.h"

#include "map_structures/world/world.h"

enum buttonsEnum
{
	SAVE = 0,
	HELP = 1,
	EXIT_TO_MENU = 2,
	SETTINGS = 3,
	SET_PAUSE = 4,
	REMOVE_PAUSE = 5,
	TICK_SPEED_1 = 6,
	TICK_SPEED_2 = 7,
	TICK_SPEED_4 = 8,
};

MainControlPanel::MainControlPanel() : UIWindow(sf::Vector2i(372, 110))
{
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
	buttons[TICK_SPEED_1] = Button("tick_speed_1.bmp", sf::Vector2i(48, 48), sf::Vector2i(310, 10));
	buttons[TICK_SPEED_2] = Button("tick_speed_2.bmp", sf::Vector2i(48, 48), sf::Vector2i(310, 10));
	buttons[TICK_SPEED_4] = Button("tick_speed_4.bmp", sf::Vector2i(48, 48), sf::Vector2i(310, 10));
	buttons[TICK_SPEED_2].setVisible(false);
	buttons[TICK_SPEED_4].setVisible(false);

	for (auto& [name, button] : buttons)
	{
		button.relocateWithOwner(position);
	}

	waveNumberText = sf::Text(turretClassic, sf::String(L"волна: "), 16);
	waveNumberText.setFillColor(standardColor);
	waveNumberText.setPosition(sf::Vector2f(10, 60));

	waveNumberText2 = sf::Text(turretClassic, sf::String(L" "), 16);
	waveNumberText2.setFillColor(standardColor);
	waveNumberText2.setPosition(sf::Vector2f(65, 60));
	

    waveTimerText = sf::Text(turretClassic, sf::String(L"до следующей волны: "), 16);
    waveTimerText.setFillColor(standardColor);
	waveTimerText.setPosition(sf::Vector2f(10, 80));
	
	waveTimerText2 = sf::Text(turretClassic, sf::String(L" "), 16);
    waveTimerText2.setFillColor(standardColor);
	waveTimerText2.setPosition(sf::Vector2f(200, 80));

	confirmationWindow = std::make_unique<ConfirmationWindow>();
}



void MainControlPanel::interact(bool& isPaused, bool& isGameplayActive, std::atomic_int& tickSpeed, const World& world)
{
	if (buttons[SAVE].press())
		world.save("save_1");
	
	if (buttons[EXIT_TO_MENU].press())
	{
		confirmationWindow->setVisible(true);
		isGameplayActive = !confirmationWindow->interact();
		confirmationWindow->setVisible(false);
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
	
	if (buttons[SET_PAUSE].press() || buttons[REMOVE_PAUSE].press() || InputHandler::jactive(t1::BindName::Pause))
	{
		std::cout << "pause button works" << std::endl;
		isPaused = !isPaused;
		buttons[SET_PAUSE].setVisible(!isPaused);
		buttons[REMOVE_PAUSE].setVisible(isPaused);
	}

	if (buttons[TICK_SPEED_1].press())
	{
		tickSpeed.store(2, std::memory_order_relaxed);
		buttons[TICK_SPEED_1].setVisible(false);
		buttons[TICK_SPEED_2].setVisible(true);
		buttons[TICK_SPEED_4].setVisible(false);
	}
	else if (buttons[TICK_SPEED_2].press())
	{
		tickSpeed.store(4, std::memory_order_relaxed);
		buttons[TICK_SPEED_1].setVisible(false);
		buttons[TICK_SPEED_2].setVisible(false);
		buttons[TICK_SPEED_4].setVisible(true);
	}
	else if (buttons[TICK_SPEED_4].press())
	{
		tickSpeed.store(1, std::memory_order_relaxed);
		buttons[TICK_SPEED_1].setVisible(true);
		buttons[TICK_SPEED_2].setVisible(false);
		buttons[TICK_SPEED_4].setVisible(false);
	}
}



void MainControlPanel::interactWaveTimer(const bool isPaused, const World& world)
{
	if(!isPaused)
	{
		std::ostringstream strWaveNumber;
		strWaveNumber << world.getTime().getWave();
		waveNumberText2.setString(strWaveNumber.str());

    	std::ostringstream strSeconds;
		strSeconds << (59 - ((world.getTime().getTime() / 60) % 60));

    	std::ostringstream strMinutes;
		strMinutes << int(2 - (world.getTime().getTime() / 3600));

    	waveTimerText2.setString(strMinutes.str() + " : " + strSeconds.str());
	}
}


void MainControlPanel::relocate(const sf::Vector2i windowSize)
{
	confirmationWindow->relocate(windowSize);
}


void MainControlPanel::draw(sf::RenderWindow& window)
{
	drawBase(window);
	for (auto& [name, button] : buttons)
		button.draw(window);
    
	window.draw(waveNumberText);
	window.draw(waveNumberText2);

    window.draw(waveTimerText);
    window.draw(waveTimerText2);

	confirmationWindow->draw(window);
}
