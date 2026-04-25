#include <iostream>
#include <vector>
#include <cstdint>
#include <string>
#include "raylib.h"
#include "raymath.h"
#pragma once

using namespace std;

void DrawShorterLineStartEnd(Vector2 start, Vector2 end, float amount, float thickness, Color color);
void DrawShorterLineStart(Vector2 start, Vector2 end, float amount, float thickness, Color color);
void DrawShorterLineEnd(Vector2 start, Vector2 end, float amount, float thickness, Color color);