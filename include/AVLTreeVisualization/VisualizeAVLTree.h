#include <iostream>
#include <vector>
#include <cstdint>
#include <string>
#include "AVLTree.h"
#include "raylib.h"
#include "raymath.h"
#pragma once

using namespace std;

extern vector < vector <RenderTexture2D> > AVLTreeScenes;

void AVLTreeScenesInit(void);
void UnloadAVLTreeScenes(void);