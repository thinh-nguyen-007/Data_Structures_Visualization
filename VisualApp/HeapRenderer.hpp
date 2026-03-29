// HeapRenderer.hpp
#pragma once
#include "HeapController.hpp"
#include "AnimationPlayer.hpp"

class HeapRenderer {
public:
    void draw(sf::RenderWindow& window, HeapController& controller, AnimationPlayer& anim, const sf::Font& font);
};