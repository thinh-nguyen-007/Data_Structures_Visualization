#include <iostream>
#include <vector>
#include "raylib.h"
#include "raymath.h"
#include "Textures.h"
#include "DrawText.h"
#include "DrawPicture.h"
#include "MyColors.h"
#pragma once

using namespace std;

extern vector <vector <RenderTexture2D> > ChooseDataScenes;
extern RenderTexture2D DrawnText;

void PreviewDataSceneInit();
void HeapDataSceneInit();
void LinkedListDataSceneInit();
void AVLTreeDataSceneInit();
void GraphDataSceneInit();
void ChooseDataSceneInit(void);
void UnloadChooseDataScene(void);