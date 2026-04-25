#include <iostream>
#include <vector>
#include <cstdint>
#include <string>
#include "DrawObjects.h"
#include "raylib.h"
#include "raymath.h"

using namespace std;

void DrawShorterLineStartEnd(Vector2 start, Vector2 end, float amount, float thickness, Color color) {
    Vector2 dir = Vector2Normalize(Vector2Subtract(end, start));
    // Vector2 newStart = Vector2Add(start, Vector2Scale(dir, amount));
    // Vector2 newEnd = Vector2Subtract(end, Vector2Scale(dir, amount));

    Vector2 newStart = start + dir * amount;
    Vector2 newEnd   = end - dir * amount;

    DrawLineEx(newStart, newEnd, thickness, color);
}

void DrawShorterLineStart(Vector2 start, Vector2 end, float amount, float thickness, Color color) {
    Vector2 dir = Vector2Normalize(Vector2Subtract(end, start));
    Vector2 newStart = start + dir * amount;

    DrawLineEx(newStart, end, thickness, color);
}

void DrawShorterLineEnd(Vector2 start, Vector2 end, float amount, float thickness, Color color) {
    Vector2 dir = Vector2Normalize(Vector2Subtract(end, start));
    Vector2 newEnd = end - dir * amount;

    DrawLineEx(start, newEnd, thickness, color);
}