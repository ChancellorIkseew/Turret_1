
#include "balance.h"
#include "map_structures/pre-settings/pre-settings.h"


Balance::Balance()
{
	balance.stone = 1000;
	balance.iron = 0;
	balance.copper = 0;
	balance.silicon = 0;
	balance.coal = 0;
	balance.sulfur = 0;
}


bool Balance::isEnough(const t1::res::AllResources expenses) const
{
	if (balance.stone < expenses.stone * PreSettings::getBuildingExpansesMidifier())
		return false;

	if (balance.iron < expenses.iron * PreSettings::getBuildingExpansesMidifier())
		return false;

	if (balance.copper < expenses.copper * PreSettings::getBuildingExpansesMidifier())
		return false;

	if (balance.silicon < expenses.silicon * PreSettings::getBuildingExpansesMidifier())
		return false;

	if (balance.coal < expenses.coal * PreSettings::getBuildingExpansesMidifier())
		return false;

	if (balance.sulfur < expenses.sulfur * PreSettings::getBuildingExpansesMidifier())
		return false;

	return true;
}


void Balance::waste(t1::res::AllResources expenses)
{
	balance.stone -= expenses.stone * PreSettings::getBuildingExpansesMidifier();
	balance.iron -= expenses.iron * PreSettings::getBuildingExpansesMidifier();
	balance.copper -= expenses.copper * PreSettings::getBuildingExpansesMidifier();
	balance.silicon -= expenses.silicon * PreSettings::getBuildingExpansesMidifier();
	balance.coal -= expenses.coal * PreSettings::getBuildingExpansesMidifier();
	balance.sulfur -= expenses.sulfur * PreSettings::getBuildingExpansesMidifier();
}
