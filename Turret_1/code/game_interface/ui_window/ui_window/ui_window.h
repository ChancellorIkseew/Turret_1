#pragma once
#ifndef SUB_WINDOW
#define SUB_WINDOW

#include "ui_plate.h"


class UIWindow : public UIPlate
{
public:
	static inline bool windowCreated = false;
	UIWindow(const sf::Vector2u size, const sf::Vector2u position);
	virtual ~UIWindow() = default;

	void relocateCentral(const sf::Vector2u wndowSize);
	virtual void relocate(const sf::Vector2u wndowSize);

};

#endif // SUB_WINDOW
