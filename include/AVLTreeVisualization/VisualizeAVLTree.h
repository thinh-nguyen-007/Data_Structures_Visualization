#include <iostream>
#include <vector>
#include <cstdint>
#include <string>
#include "AVLTree.h"
#include "Items.h"
#include "raylib.h"
#include "raymath.h"
#pragma once

using namespace std;

struct VisualizedTree {
    line edge;
    circle node;
    long long data;

    VisualizedTree* left;
    VisualizedTree* right;
    

    VisualizedTree(long long data = 0, Vector2 pos = {0, 0}, Vector2 targetPos = {0, 0}) {
        this->data = data;
        node = circle(pos, targetPos, 50.0f, 5.0f, WHITE);
        edge = line(pos, pos, pos, pos, 5.0f, BLACK);
        left = right = nullptr;
    }
};

extern vector < vector <RenderTexture2D> > AVLTreeScenes;
extern vector <pair <long long , int> > RotateState;
extern float totWidth;
extern float totHeight;
extern VisualizedTree* FindNode;
extern vector <VisualizedTree*> VisualizedNodes;
extern vector <VisualizedTree*> AVLTreeState;
extern vector <VisualizedTree*> AVLTreeScene;

void CreateAVLTreeScene(void);
void DeployAVLTreeVisualization(void);
void DrawAllAVLTree(void);
void AVLTreeScenesInit(void);
void PrepareAVLTree(void);
void AVLTreeScenesDeployment(void);
void UnloadAVLTreeScenes(void);
void RecuresiveDraw(AVLTree::node* tree, VisualizedTree* visualizedNode, Vector2 parpos, float depth, float spacing, float distance);
void OutputTree(void);
void FlattenTheTree(VisualizedTree* AVLTree, vector <VisualizedTree*> &VisualizedNodes, vector <VisualizedTree*> &version2, long long FixedPoint);
void ComputeInformation(void);