#pragma once
#ifndef T1_LABEL_H
#define T1_LABEL_H

#include <SFML/Graphics.hpp>
#include "game_interface/ui_window/sub_win_util/fonts.h"


class Label
{
private:
    sf::Vector2i position;
    sf::Text text = sf::Text(turretClassic);
    bool isVisible = true;

public:
    Label(const sf::String& string, const sf::Vector2i position);
    Label() = default;
    ~Label() = default;

    void setVisible(const bool visible);

    void relocateWithOwner(const sf::Vector2i ownerPosition);
    void draw(sf::RenderWindow& window);

};

#endif // T1_LABEL_H
