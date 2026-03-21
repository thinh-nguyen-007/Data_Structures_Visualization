// AnimationPlayer.hpp
#pragma once
#include "HeapController.hpp"

class AnimationPlayer {
private:
    float delay = 0.5f;
    float accumulator = 0.f;
public:
    void update(float dt, HeapController& controller);
    void setDelay(float d);
};