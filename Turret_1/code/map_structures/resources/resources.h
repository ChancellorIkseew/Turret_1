#pragma once
#ifndef RESOURCES_H
#define RESOURCES_H

#include <string>

namespace t1::res
{
	extern int stoneQuantity;
	extern int ironQuantity;
	extern int copperQuantity;
	extern int siliconQuantity;
	extern int coalQuantity;
	extern int oilQuantity;
	extern int sulfurQuantity;

	extern int newEnergy;
	extern int oldEnergy;

	struct AllResources
	{
		int stoneQuant;
		int ironQuant;
		int copperQuant;
		int siliconQuant;
		int coalQuant;
		int sulfurQuant;
	};

	// Utilites

	void giveStartResources();

	void loadResources(std::string saveFolderName);

	void saveResources(std::string saveFolderName);

	// Interaction

	void sendToBalance(int type, short amount);

	bool isEnoughAllRes(AllResources expenses);

	void wasteRes(AllResources expenses);

	void useEnergy(int time);
};

#endif // RESOURCES_H
