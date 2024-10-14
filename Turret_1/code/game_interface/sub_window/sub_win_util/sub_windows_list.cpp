
#include "sub_windows_list.h"

#include "game_interface/gameplay/sub_windows/exit_confirmation.h"
#include "game_interface/gameplay/sub_windows/settings_window.h"
#include "game_interface/gameplay/sub_windows/resources_panel.h"
#include "game_interface/gameplay/sub_windows/main_control_panel.h"
#include "game_interface/gameplay/sub_windows/specifications_panel.h"
#include "game_interface/gameplay/sub_windows/building_panel.h"





void initSubWindows()
{
	
}


void relocateSubWindows(const sf::Vector2u windowSize)
{
	ConfirmationWindow::getInstance().relocate(windowSize);
	SettingsWindow::getInstance().relocate(windowSize);
	ResourcesPanel::getInstance().relocate(windowSize);
	BuildingPanel::getInstance().relocate(windowSize);

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
