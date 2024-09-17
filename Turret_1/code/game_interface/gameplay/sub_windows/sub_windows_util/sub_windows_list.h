#pragma once
#ifndef SUB_WINDOWS_LIST
#define SUB_WINDOWS_LIST

#include <SFML/Graphics.hpp>
#include <list>

#include "../exit_confirmation.h"
#include "../settings_window.h"
#include "../resources_panel.h"
#include "../main_control_panel.h"
#include "../building_panel.h"

#include "sub_window.h"
#include "../../../system/system.h"

extern ConfirmationWindow confWin;
extern SettingsWindow settingsWindow;
extern ResourcesPanel resWin;
extern MainControlPanel mainControlPanel;
extern BuildingPanel buildingPanel;


extern std::list<SubWindow*> SubWindowsList;

void initSubWindows();

void relocateSubWindows(int windowSizeX, int windowSizeY);

bool noSubWindowSelected(sf::Vector2i mouseCoord);



#endif // SUB_WINDOWS_LIST