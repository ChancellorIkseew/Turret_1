#pragma once
#ifndef SUB_WINDOW
#define SUB_WINDOW

#include "ui_plate.h"


class UIWindow : public UIPlate
{
public:
	static inline bool windowCreated = false;
	UIWindow(const sf::Vector2i size, const sf::Vector2i position);
	UIWindow(const sf::Vector2i size);
	virtual ~UIWindow() = default;

	void relocateCentral(const sf::Vector2i wndowSize);
	virtual void relocate(const sf::Vector2i wndowSize);

};

#endif // SUB_WINDOW
