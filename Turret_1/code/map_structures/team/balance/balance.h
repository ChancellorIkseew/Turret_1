#pragma once
#ifndef TEAM_BALANCE_H
#define TEAM_BALANCE_H

#include "map_structures/resources/resources.h"

class Balance
{
private:
	

public:
	t1::res::AllResources balance;

	Balance();

	void giveStartResources();

	//void loadResources(std::string saveFolderName);
	//void saveResources(std::string saveFolderName);

	// Interaction

	void send(int type, short amount);
	bool isEnough(const t1::res::AllResources expenses) const;
	void waste(t1::res::AllResources expenses);

};

#endif // TEAM_BALANCE_H
