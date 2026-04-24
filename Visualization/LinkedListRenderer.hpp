#pragma once
#include <SFML/Graphics.hpp>
#include "LinkedListCommand.hpp"
#include "Animation.hpp"

class LinkedListRenderer {
public:
    // draw main linked list (node + arrow + highlight + animation)
    void draw(sf::RenderWindow& window,
              LinkedListController& controller,
              Animation& anim,
              const sf::Font& font);

    // optional: draw array/table view (debug hoặc bonus điểm)
    void drawTable(sf::RenderWindow& window,
                   LinkedListController& controller,
                   const sf::Font& font);
};