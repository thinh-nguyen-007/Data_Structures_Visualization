// AnimationPlayer.cpp
#include "AnimationPlayer.hpp"

void AnimationPlayer::update(float dt, HeapController& controller) {
    if (!controller.hasSteps()) return;
    accumulator += dt;
    if (accumulator >= delay) {
        controller.nextStep();
        accumulator = 0.f;
    }
}
void AnimationPlayer::setDelay(float d) {
    delay = d;
}