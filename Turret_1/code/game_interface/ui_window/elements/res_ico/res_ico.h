#pragma once
#ifndef RES_ICO_H
#define RES_ICO_H

#include <SFML\Graphics.hpp>


class ResIco
{
private:
	static inline sf::Image image;
	static inline sf::Texture texture;
	static inline sf::Sprite ico;

	int resType;
	sf::Vector2u position;
	sf::Vector2u ownerPosition;

	ResIco(const ResIco& other) = delete;
	ResIco& operator=(const ResIco& other) = delete;

public:
	ResIco();
	ResIco(const int resType, const sf::Vector2u position);
	ResIco(const ResIco&& other) noexcept;
	ResIco& operator=(const ResIco&& other) noexcept;
	~ResIco() = default;

	void setResType(const int resType);
	void relocate(const sf::Vector2u ownerPosition);

	static void prepareSprites();
	void draw(sf::RenderWindow& window) const;

};

#endif // RES_ICO_H
