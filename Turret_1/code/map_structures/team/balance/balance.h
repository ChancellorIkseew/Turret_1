#pragma once
#ifndef TEAM_BALANCE_H
#define TEAM_BALANCE_H

#include "map_structures/resources/all_resources.h"

class Balance
{
private:
	

public:
	AllResources balance;

	Balance();

	void giveStartRes(const std::map<int, int>& startRes);

	//void loadResources(std::string saveFolderName);
	//void saveResources(std::string saveFolderName);

	// Interaction

	void accept(int type, short amount);
	bool isEnough(const AllResources& expenses) const;
	void waste(const AllResources& expenses);

};

#endif // TEAM_BALANCE_H
