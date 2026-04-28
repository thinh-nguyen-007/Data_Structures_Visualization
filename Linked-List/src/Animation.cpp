#include "Animation.hpp"
#include "Design.hpp"
#include <cmath>
#include <cstdlib>

// ===== compute node position (LINEAR LAYOUT) =====
static sf::Vector2f computeNodePos(int i, float width) {
    float spacing = 80.f;
    float startX = width / 2.f - spacing * 3; // center list
    float x = startX + i * spacing;
    float y = 300.f;

    return { x, y };
}

// ===== update =====
void LinkedListAnimation::update(float dt, LinkedListController& controller, float width) {
    accumulator += dt;

    if (!controller.isPaused() && controller.isBusy() && accumulator >= delay) {
        controller.nextStep();

        const LinkedListStep& step = controller.getCurrentStep();

        if (step.type == LinkedListStep::Done) {
            controller.setPaused(true);
        }

        if (step.type == LinkedListStep::Insert) {
            spawnInsertEffect(step.index, width);
        }

        if (step.type == LinkedListStep::Delete) {
            spawnRemoveEffect(step.index, width);
        }

        if (step.type == LinkedListStep::Traverse) {
            spawnTraverseEffect(step.index, width);
        }

        if (step.type == LinkedListStep::Found) {
            spawnInsertEffect(step.index, width); // highlight effect
        }

        accumulator = 0.f;
    }

    updateStars(dt);
}

// ===== delay =====
void LinkedListAnimation::setDelay(float d) {
    delay = d;
}

// ===== get stars =====
const std::vector<LinkedListAnimation::Star>& LinkedListAnimation::getStars() const {
    return stars;
}

// ===== update particles =====
void LinkedListAnimation::updateStars(float dt) {
    for (auto it = stars.begin(); it != stars.end();) {
        it->lifetime -= dt;

        it->offsetX += it->velocityX * dt;
        it->offsetY += it->velocityY * dt;

        if (it->lifetime <= 0.f)
            it = stars.erase(it);
        else
            ++it;
    }
}

// ===== insert effect =====
void LinkedListAnimation::spawnInsertEffect(int idx, float width) {
    sf::Vector2f base = computeNodePos(idx, width);

    for (int i = 0; i < 15; i++) {
        float angle = (i / 15.f) * 2.f * 3.14159f;
        float speed = 80.f + rand() % 40;

        Star s;
        s.basePos = base;
        s.velocityX = std::cos(angle) * speed;
        s.velocityY = std::sin(angle) * speed;
        s.lifetime = 0.6f;
        s.color = StarColor::random(); // xanh / sáng

        stars.push_back(s);
    }
}

// ===== remove effect =====
void LinkedListAnimation::spawnRemoveEffect(int idx, float width) {
    if (idx < 0) return;

    sf::Vector2f base = computeNodePos(idx, width);

    for (int i = 0; i < 18; i++) {
        float angle = (i / 18.f) * 2.f * 3.14159f;
        float speed = 150.f + rand() % 80;

        Star s;
        s.basePos = base;
        s.velocityX = std::cos(angle) * speed;
        s.velocityY = std::sin(angle) * speed;
        s.lifetime = 0.4f;
        s.color = DeepColor::random(); // đỏ / đậm

        stars.push_back(s);
    }
}

// ===== traverse effect (NEW - IMPORTANT) =====
void LinkedListAnimation::spawnTraverseEffect(int idx, float width) {
    if (idx < 0) return;

    sf::Vector2f base = computeNodePos(idx, width);

    for (int i = 0; i < 10; i++) {
        float angle = (i / 10.f) * 2.f * 3.14159f;
        float speed = 40.f + rand() % 20;

        Star s;
        s.basePos = base;
        s.velocityX = std::cos(angle) * speed;
        s.velocityY = std::sin(angle) * speed;
        s.lifetime = 0.3f;
        s.color = sf::Color::Yellow; // highlight traversal

        stars.push_back(s);
    }
}