// HeapRenderer.hpp
#pragma once
#include <SFML/Graphics.hpp>
#include "HeapController.hpp"

class HeapRenderer {
public:
    void draw(sf::RenderWindow& window, HeapController& controller, sf::Font& font);
};