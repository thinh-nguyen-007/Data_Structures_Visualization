// AnimationPlayer.cpp
#include "AnimationPlayer.hpp"
#include "Design.hpp"
#include <cmath>
#include <cstdlib>

// helper (same logic as renderer)
static sf::Vector2f computeNodePos(int i, float width) {
    int level = std::floor(std::log2(i + 1));
    int nodes = 1 << level;
    int idx = i - (nodes - 1);

    float x = width / (nodes + 1) * (idx + 1);
    float y = 150.f + level * 80.f;

    return { x, y };
}

void AnimationPlayer::update(float dt, HeapController& controller, float width) {
    accumulator += dt;

    if (controller.hasSteps() && accumulator >= delay) {

        auto nextType = controller.peekNextStepType();

        int removeIndex = -1;
        if (nextType == HeapStep::Remove) {
            removeIndex = controller.peekNextA(); // BEFORE delete
        }

        controller.nextStep();

        // ================= INSERT =================
        if (nextType == HeapStep::Insert) {

            int idx = controller.getHeap().getSize() - 1;
            sf::Vector2f base = computeNodePos(idx, width);

            for (int i = 0; i < 15; i++) {
                float angle = (i / 15.f) * 2.f * 3.14159f;
                float speed = 80.f + rand() % 40;

                Star s;
                s.basePos = base;
                s.velocityX = std::cos(angle) * speed;
                s.velocityY = std::sin(angle) * speed;
                s.lifetime = 0.6f;
                s.color = StarColor::random();

                stars.push_back(s);
            }
        }

        // ================= DELETE =================
        if (nextType == HeapStep::Remove && removeIndex != -1) {

            sf::Vector2f base = computeNodePos(removeIndex, width);

            for (int i = 0; i < 18; i++) {
                float angle = (i / 18.f) * 2.f * 3.14159f;
                float speed = 150.f + rand() % 80;

                Star s;
                s.basePos = base;
                s.velocityX = std::cos(angle) * speed;
                s.velocityY = std::sin(angle) * speed;
                s.lifetime = 0.4f;
                s.color = DeepColor::random();

                stars.push_back(s);
            }
        }

        accumulator = 0.f;
    }

    // ================= UPDATE STARS =================
    for (auto it = stars.begin(); it != stars.end(); ) {
        it->lifetime -= dt;

        it->offsetX += it->velocityX * dt;
        it->offsetY += it->velocityY * dt;

        if (it->lifetime <= 0.f)
            it = stars.erase(it);
        else
            ++it;
    }
}

void AnimationPlayer::setDelay(float d) {
    delay = d;
}

const std::vector<AnimationPlayer::Star>& AnimationPlayer::getStars() const {
    return stars;
}