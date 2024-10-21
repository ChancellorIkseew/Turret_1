#pragma once
#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

inline char32_t symbol = '?';

enum GameCondition
{
	MAIN_MENU = 'm',
	CHOISE_FOLDER_MENU = 'c',
	PRE_SETTINGS_MENU = 'p',
	GAMEPLAY = 'g',
	OPTIONS,
	EXIT
};

void openMainWindow();


#endif // MAIN_WINDOW_H
