
#include "sub_windows_list.h"

#include "../exit_confirmation.h"
#include "../settings_window.h"
#include "../resources_panel.h"
#include "../main_control_panel.h"
#include "../specifications_panel.h"
#include "../building_panel.h"


std::list<SubWindow*> SubWindowsList;

ConfirmationWindow confWin;
ResourcesPanel resWin;
SettingsWindow settingsWindow;
MainControlPanel mainControlPanel;
BuildingPanel buildingPanel;

void initSubWindows()
{
	
	



}


void relocateSubWindows(int windowSizeX, int windowSizeY)
{
	confWin.relocate(windowSizeX, windowSizeY);
	settingsWindow.relocate(windowSizeX, windowSizeY);
	resWin.relocate(windowSizeX, windowSizeY);
	SpecificationsPanel::getInstance()->relocate(windowSizeX, windowSizeY);
	buildingPanel.relocate(windowSizeX, windowSizeY);

}



bool noSubWindowSelected(sf::Vector2i mouseCoord)
{
	if (!mainControlPanel.containsCoursor(mouseCoord) && !resWin.containsCoursor(mouseCoord) &&
		!buildingPanel.containsCoursor(mouseCoord) && !SpecificationsPanel::getInstance()->containsCoursor(mouseCoord))
	{
		return true;
	}

	return false;
}