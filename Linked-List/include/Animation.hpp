#pragma once
#include "LinkedListCommand.hpp"
#include <SFML/Graphics.hpp>
#include <vector>

class LinkedListAnimation {
private:
    float delay = 0.5f;
    float accumulator = 0.f;

    struct Star {
        sf::Vector2f basePos;
        float offsetX = 0.f, offsetY = 0.f;
        float velocityX = 0.f, velocityY = 0.f;
        float lifetime = 0.f;
        sf::Color color;
    };

    std::vector<Star> stars;

    // ===== Effects =====
    void spawnInsertEffect(int idx, float width);
    void spawnRemoveEffect(int idx, float width);
    void spawnTraverseEffect(int idx, float width);

    void updateStars(float dt);

public:
    // update animation (core loop)
    void update(float dt, LinkedListController& controller, float width);

    // control speed
    void setDelay(float d);

    // get particles
    const std::vector<Star>& getStars() const;
};