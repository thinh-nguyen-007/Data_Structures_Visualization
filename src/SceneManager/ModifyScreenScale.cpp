#include <iostream>
#include <string>
#include <vector>
#include <cstdint>
#include "raylib.h"
#include "raymath.h"
#include "ModifyScreenScale.h"

using namespace std;

void ScaleTheScreen(Camera2D &camera) {
    // 🔹 Zoom with mouse wheel
    float wheel = GetMouseWheelMove();
    if (wheel != 0) {
        camera.zoom += wheel * 0.1f;

        // limit zoom range
        if (camera.zoom < 0.2f) camera.zoom = 0.2f;
        if (camera.zoom > 3.0f) camera.zoom = 3.0f;
    }

    // 🔹 Move camera (drag with left mouse)
    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
        Vector2 delta = GetMouseDelta();
        delta = Vector2Scale(delta, -1.0f / camera.zoom);
        camera.target = Vector2Add(camera.target, delta);
    }
}