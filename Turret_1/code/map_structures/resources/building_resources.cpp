
#include "resources.h"
#include "map_structures/pre-settings/pre-settings.h"


bool isEnoughAllRes(AllResources expenses)
{
	
	if(stoneQuantity < expenses.stoneQuant * PreSettings::getBuildingExpansesMidifier())
		return false;
	
	if(ironQuantity < expenses.ironQuant * PreSettings::getBuildingExpansesMidifier())
		return false;
	
	if(copperQuantity < expenses.copperQuant * PreSettings::getBuildingExpansesMidifier())
		return false;
	
	if(siliconQuantity < expenses.siliconQuant * PreSettings::getBuildingExpansesMidifier())
		return false;
	
	if(coalQuantity < expenses.coalQuant * PreSettings::getBuildingExpansesMidifier())
		return false;
	
	if(sulfurQuantity < expenses.sulfurQuant * PreSettings::getBuildingExpansesMidifier())
		return false;
	
	return true;
}



void wasteRes(AllResources expenses)
{
	
	stoneQuantity -= expenses.stoneQuant * PreSettings::getBuildingExpansesMidifier();
	
	ironQuantity -= expenses.ironQuant * PreSettings::getBuildingExpansesMidifier();
	
	copperQuantity -= expenses.copperQuant * PreSettings::getBuildingExpansesMidifier();
	
	siliconQuantity -= expenses.siliconQuant * PreSettings::getBuildingExpansesMidifier();
	
	coalQuantity -= expenses.coalQuant * PreSettings::getBuildingExpansesMidifier();
	
	sulfurQuantity -= expenses.sulfurQuant * PreSettings::getBuildingExpansesMidifier();
	
}
