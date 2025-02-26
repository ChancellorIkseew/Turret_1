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
	static inline sf::Sprite ico;

	ResType resType = ResType::NO_RESOURCES;
	sf::Vector2u position = sf::Vector2u(0, 0);
	sf::Vector2u ownerPosition = sf::Vector2u(0, 0);

	ResIco(const ResIco& other) = delete;
	ResIco& operator=(const ResIco& other) = delete;

public:
	ResIco(const ResType resType, const sf::Vector2u position);
	ResIco(const ResIco&& other) noexcept;
	ResIco& operator=(const ResIco&& other) noexcept;
	ResIco() = default;
	~ResIco() = default;

	void setResType(const ResType resType);
	void relocate(const sf::Vector2u ownerPosition);

	static void prepareSprites();
	void draw(sf::RenderWindow& window) const;

};

#endif // RES_ICO_H
