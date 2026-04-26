#include <iostream>
#include <vector>
#include <string>
#include <cstdint>
#include "raylib.h"
#include "raymath.h"
#pragma once

using namespace std;

extern Texture2D TestBackground;
extern Texture2D Background;
extern Font MyFont;

void LoadTextures(void);
void UnloadTextures(void);