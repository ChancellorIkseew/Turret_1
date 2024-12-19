
#include "balance.h"
#include "map_structures/pre-settings/pre-settings.h"


Balance::Balance()
{
	balance = AllResources(0, 0, 0, 0, 0, 0);
}

void Balance::save(cereal::BinaryOutputArchive& archive) const
{
	archive(balance);
}

void Balance::load(cereal::BinaryInputArchive& archive)
{
	archive(balance);
}

void Balance::accept(int type, short amount)
{
	balance.allResources[type] += amount;
}

void Balance::giveStartRes(const std::map<int, int>& startRes)
{
	balance = startRes;
}


bool Balance::isEnough(const AllResources& expenses) const
{
	for (auto& res : expenses.allResources)
	{
		int index = res.first;
		if (balance.allResources.find(index)->second < expenses.allResources.find(index)->second * PreSettings::getBuildings().expensesModifier)
			return false;
	}
	return true;
}


void Balance::waste(const AllResources& expenses)
{
	for (auto& res : expenses.allResources)
	{
		int index = res.first;
		balance.allResources.find(index)->second -= expenses.allResources.find(index)->second * PreSettings::getBuildings().expensesModifier;
	
	}
}
