#pragma once
#ifndef T1_BUTTON_H
#define T1_BUTTON_H

#include <SFML/Graphics.hpp>
#include <string>


class Button
{
private:

    sf::Vector2i size;
    sf::Vector2i position;

    sf::Image image;
    sf::Texture texture;
    sf::Sprite button;
    sf::String name;

    bool isVisible = true;
    bool isSelected = false;
    bool isPressed = false;

	static bool anyButtonSelected;

public:
    Button(const std::string& imageFile, const sf::Vector2i size, const sf::Vector2i position);
    Button() = default;
    Button& operator=(const Button& other);
    ~Button() = default;
    

    bool select(const sf::Vector2i& mouseCoord);
    bool press(const sf::Vector2i& mouseCoord);
    void setVisible(const bool visible);

    void relocate(const sf::Vector2i subWinPosition);
    void draw(sf::RenderWindow& window);

};

#endif // T1_BUTTON_H
