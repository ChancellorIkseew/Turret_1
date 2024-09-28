
#include "shells_list.h"


std::list<std::unique_ptr<Shell>> t1::sh::playerShellsList;		//Player's shels
std::list<std::unique_ptr<Shell>> t1::sh::enemyShellsList;	//Enemie's shels


void t1::sh::saveShellsList(const std::string& folder)
{

}

void t1::sh::loadShellsList(const std::string& folder)
{

}


void t1::sh::moveShellsList()
{
	for (auto it = playerShellsList.begin(); it != playerShellsList.end();)
	{
		(*it)->motion();
		(*it)->tryPlayerShellsHitting();

		if ((*it)->getIsWasted())
		{
			(*it)->explosion();
			it = playerShellsList.erase(it);
		}
		else
			++it;
	}

	for (auto it = enemyShellsList.begin(); it != enemyShellsList.end();)
	{
		(*it)->motion();
		(*it)->tryEnemyShellsHitting();

		if ((*it)->getIsWasted())
		{
			(*it)->explosion();
			it = enemyShellsList.erase(it);
		}
		else
			++it;
	}
}


void t1::sh::drawShellsList(sf::RenderWindow& window, int time)
{
	for (auto it = playerShellsList.begin(); it != playerShellsList.end(); ++it)
	{
		(*it)->draw(window, time);

	}

	for (auto it = enemyShellsList.begin(); it != enemyShellsList.end(); ++it)
	{
		(*it)->draw(window, time);
	}
}


void t1::sh::cleanShellsList()
{
	playerShellsList.clear();
	enemyShellsList.clear();
}
