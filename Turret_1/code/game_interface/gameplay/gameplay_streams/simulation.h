#pragma once
#ifndef T1_GAMMEPL_SIMULATION
#define T1_GAMMEPL_SIMULATION

class Team;

namespace t1::gamepl
{
	void simulation(const bool& isGameplayActive, const bool& isPaused, Team& enemy, Team& player);
}


#endif // T1_GAMMEPL_SIMULATION
