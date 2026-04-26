#include <iostream>
#include <vector>
#include "raylib.h"
#include "raymath.h"
#pragma once

using namespace std;

extern float RectangleWidth, RectangleHeight;
extern vector <RenderTexture2D> StartingScenes;
extern RenderTexture2D test;

void StartingSceneInit(void);
void UnloadStartingScene(void);