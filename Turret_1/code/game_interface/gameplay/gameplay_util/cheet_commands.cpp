#ifndef TURRET_NO_TEST_BUILD

#include <iostream>

#include "cheet_commands.h"

#include "../../../map_structures/base_engine/test.h"

#include "../../../map_structures/resources/resources.h"
#include "../../../map_structures/resources/res_enum.h"
#include "../../../map_structures/entities/entities.h"
#include "../../../map_structures/entities/mob_types/standard_bot.h"
#include "../../../map_structures/entities/entities_util/entities_list.h"


void acceptCheetCommand()
{
	std::cout << "cheet_comands_panel_is_activated" << '\n';

	while (true)
	{
		char command;
		std::cin >> command;

		switch (command)
		{
			case 'r':
			{
				std::cout << "enter_res_type_and_amount example : 1 1000" << '\n';
				int resType;
				int resAmount;
				std::cin >> resType >> resAmount;
				if (resType > 0 && resType < 7)
				{
					sendToBalance(resType, resAmount);
				}
				else
				{
					std::cout << "command_was_not_identified : this_resource_type_does_not_exist" << '\n';
				}
				break;
			}

			case 'u':
			{
				sendToBalance(RES_STONE, 10000);
				sendToBalance(RES_IRON, 10000);
				sendToBalance(RES_COPPER, 10000);
				sendToBalance(RES_SILICON, 10000);
				sendToBalance(RES_COAL, 10000);
				sendToBalance(RES_SULFUR, 10000);
				break;
			}
			
			case 'm':
			{
				std::cout << "enter_'k'_to_kill_all_enemy_mobs" << '\n';
				char act;
				std::cin >> act;
				if (act == 'k')
				{
					cleanEntitiesList();
				}
				if (act == 'n')
				{
					entitiesList.push_back(new StandardBot('1', 8, 8, 0, 100));
				}
				break;
			}

			case 't':
			{
				spiralTest();
				break;
			}
			
			case 'c':
			{
				std::cout << "cheet_comands_panel_closed" << '\n';
				return;
			}

			default:
			{
				std::cout << "command_was_not_identified" << '\n';
				break;
			}
		}
	}
}

#endif // TURRET_NO_TEST_BUILD
