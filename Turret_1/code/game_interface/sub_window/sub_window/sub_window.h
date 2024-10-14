#pragma once
#ifndef SUB_WINDOW
#define SUB_WINDOW

#include <SFML/Graphics.hpp>


class SubWindow
{
protected:
	
	char windowType;

	sf::Vector2u size;
	sf::Vector2u position;

	bool isSelected;
	bool isVisible;

	static inline sf::Image baseImage;
	static inline sf::Texture baseTexture;
	static inline sf::Sprite baseSprite;

	//Borders
	static inline sf::Image upperBorderImage;
	static inline sf::Texture upperBorderTexture;
	static inline sf::Sprite upperBorderSprite;

	static inline sf::Image lowerBorderImage;
	static inline sf::Texture lowerBorderTexture;
	static inline sf::Sprite lowerBorderSprite;

	static inline sf::Image leftBorderImage;
	static inline sf::Texture leftBorderTexture;
	static inline sf::Sprite leftBorderSprite;

	static inline sf::Image rightBorderImage;
	static inline sf::Texture rightBorderTexture;
	static inline sf::Sprite rightBorderSprite;

	//Corners
	static inline sf::Image upperLeftCornerImage;
	static inline sf::Texture upperLeftCornerTexture;
	static inline sf::Sprite upperLeftCornerSprite;

	static inline sf::Image lowerLeftCornerImage;
	static inline sf::Texture lowerLeftCornerTexture;
	static inline sf::Sprite lowerLeftCornerSprite;

	static inline sf::Image upperRightCornerImage;
	static inline sf::Texture upperRightCornerTexture;
	static inline sf::Sprite upperRightCornerSprite;

	static inline sf::Image lowerRightCornerImage;
	static inline sf::Texture lowerRightCornerTexture;
	static inline sf::Sprite lowerRightCornerSprite;

	void drawSubWindowBase(sf::RenderWindow& window);

public:

	SubWindow(char type, const sf::Vector2u size, const sf::Vector2u position);
	virtual ~SubWindow() = default;

	static void init();

	void setVisible(bool value);
	void SetSize();
	sf::Vector2i getSize() const;

	void setPosition(const sf::Vector2u position);
	void relocateCentral(const sf::Vector2u wndowSize);
	virtual void relocate(const sf::Vector2u wndowSize);

	bool containsCoursor(const sf::Vector2i& mouseCoord) const;

	static void prepareWindowBaseSprites();
	virtual void prepareInterfaceSprites() = 0;
	virtual void draw(sf::RenderWindow& window);

};

#endif // SUB_WINDOW
