#pragma once
#ifndef T1_CHECKBOX_H
#define T1_CHECKBOX_H

#include <SFML/Graphics.hpp>

class Checkbox
{
private:
    sf::Vector2i localPosition;
    sf::Vector2f absolutePosition;

    static inline sf::Image image;
    static inline sf::Texture texture;
    static inline sf::Sprite button = sf::Sprite(texture);

    bool isVisible = true;
    bool isSelected = false;
    bool isPressed = false;
    bool select();

public:
    Checkbox(const bool startValue, const sf::Vector2i position);
    Checkbox() = default;
    ~Checkbox() = default;

    bool press();
    bool getValue() const { return isPressed; }

    void relocateWithOwner(const sf::Vector2i ownerPosition);
    static void prepareSprites();
    void draw(sf::RenderWindow& window) const;

};

#endif // T1_CHECKBOX_H
