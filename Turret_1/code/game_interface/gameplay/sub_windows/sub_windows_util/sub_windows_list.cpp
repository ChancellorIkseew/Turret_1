
#include "sub_windows_list.h"

#include "../exit_confirmation.h"
#include "../settings_window.h"
#include "../resources_panel.h"
#include "../main_control_panel.h"
#include "../specifications_panel.h"
#include "../building_panel.h"


std::list<SubWindow*> SubWindowsList;


void initSubWindows()
{
	
}


void relocateSubWindows(int windowSizeX, int windowSizeY)
{
	ConfirmationWindow::getInstance().relocate(windowSizeX, windowSizeY);
	SettingsWindow::getInstance().relocate(windowSizeX, windowSizeY);
	ResourcesPanel::getInstance().relocate(windowSizeX, windowSizeY);
	SpecificationsPanel::getInstance().relocate(windowSizeX, windowSizeY);
	BuildingPanel::getInstance().relocate(windowSizeX, windowSizeY);

}


bool noSubWindowSelected(sf::Vector2i mouseCoord)
{
	if (!MainControlPanel::getInstance().containsCoursor(mouseCoord) && !ResourcesPanel::getInstance().containsCoursor(mouseCoord) &&
		!BuildingPanel::getInstance().containsCoursor(mouseCoord) && !SpecificationsPanel::getInstance().containsCoursor(mouseCoord))
	{
		return true;
	}

	return false;
}
