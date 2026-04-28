#include <iostream>
#include <vector>
#include <cstdint>
#include <string>
#include "VisualizeAVLTree.h"
#include "raylib.h"
#include "raymath.h"
#pragma once

using namespace std;

void InsertNodeAVLTreeScene(vector <VisualizedTree*> &InsertVisualizedNodes);    
void RotateAVLTreeScene(VisualizedTree* node);
void DrawInsertAVLTreeScene(void);
