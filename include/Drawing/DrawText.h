#include <iostream>
#include <raylib.h>
#include <raymath.h>
#pragma once

using namespace std;

void DrawGlowText(Font FONT, const char* text, Vector2 position, int fontSize, int spacing, Color glowColor, Color textColor);
void DrawNormalText(Font FONT, const char* text, Vector2 position, int fontSize, int spacing, Color textColor);