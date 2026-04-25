#include <iostream>
#include <vector>
#include <cstdint>
#include <string>
#include "AVLTree.h"
#include "raylib.h"
#include "raymath.h"
#pragma once

using namespace std;

struct VisualizedTree;

extern vector < vector <RenderTexture2D> > AVLTreeScenes;
extern float totWidth;
extern float totHeight;

void AVLTreeScenesInit(void);
void PrepareAVLTree(void);
void AVLTreeScenesDeployment(void);
void UnloadAVLTreeScenes(void);
void DrawAVLTree(void);
void RecuresiveDraw(AVLTree::node* tree, VisualizedTree* visualizedNode, Vector2 parpos, float depth, float spacing, float distance);
void OutputTree(void);