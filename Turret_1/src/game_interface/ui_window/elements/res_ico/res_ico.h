#pragma once
#ifndef RES_ICO_H
#define RES_ICO_H

#include <SFML\Graphics.hpp>
#include "map_structures/resources/res_enum.h"


class ResIco
{
private:
	static inline sf::Image image;
	static inline sf::Texture texture;
	static inline sf::Sprite ico = sf::Sprite(texture);

	ResType resType = ResType::NO_RESOURCES;
	sf::Vector2i localPosition;
	sf::Vector2f absolutePosition;

public:
	ResIco(const ResType resType, const sf::Vector2i position);
	ResIco() = default;
	~ResIco() = default;

	void setResType(const ResType resType);
	void setPosition(const sf::Vector2i position);
	void relocate(const sf::Vector2i ownerPosition);

	static void prepareSprites();
	void draw(sf::RenderWindow& window) const;

};

#endif // RES_ICO_H
