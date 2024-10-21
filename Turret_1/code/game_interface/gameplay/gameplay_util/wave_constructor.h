#pragma once
#ifndef WAVE_CONSTRUCTOR_H
#define WAVE_CONSTRUCTOR_H

class Team;

void createWave(Team& enemy);
void switchEntities(const int wave, Team& enemy);

#endif // WAVE_CONSTRUCTOR_H
