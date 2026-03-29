// AnimationPlayer.hpp
#pragma once
#include "HeapController.hpp"
#include <SFML/Graphics.hpp>
#include <vector>

class AnimationPlayer {
private:
    float delay = 0.5f;
    float accumulator = 0.f;

    struct Star {
        sf::Vector2f basePos; //  replaced nodeIndex

        float offsetX = 0.f, offsetY = 0.f;
        float velocityX = 0.f, velocityY = 0.f;
        float lifetime = 0.f;

        sf::Color color;
    };

    std::vector<Star> stars;

public:
    void update(float dt, HeapController& controller, float width);
    void setDelay(float d);
    const std::vector<Star>& getStars() const;
};