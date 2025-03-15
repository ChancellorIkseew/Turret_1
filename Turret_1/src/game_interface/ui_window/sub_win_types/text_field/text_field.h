#pragma once

#ifndef TEXT_FIELD_H
#define TEXT_FIELD_H

#include <SFML\Graphics.hpp>
#include "game_interface/ui_window/ui_window/ui_window.h"
#include "game_interface/ui_window/sub_win_util/fonts.h"


class TextField : public UIPlate
{
private:
	int8_t maxLenght;
	sf::Text text = sf::Text(turretClassic);
	sf::Vector2i ownerPosition;
	static inline bool isOneSelected = false;

public:
	TextField(const sf::String& value, const int sizeX, const sf::Vector2i position);
	TextField();
	~TextField() = default;

	void interact();
	void relocateWithOwner(const sf::Vector2i ownerPosition);
	static bool isOneSeltcted() { return isOneSelected; }

	void setText(const sf::String& value);
	uint32_t getValueUint32();
	float getValueFloat();

	void prepareInterfaceSprites() override final;
	void draw(sf::RenderWindow& window) override final;

};

#endif // TEXT_FIELD_H
