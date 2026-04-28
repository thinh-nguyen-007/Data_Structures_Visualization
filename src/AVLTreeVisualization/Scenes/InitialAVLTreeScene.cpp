#include <iostream>
#include <vector>
#include <string>
#include <cstdint>
#include <queue>
#include "InitialAVLTreeScene.h"
#include "VisualizeAVLTree.h"
#include "DrawObjects.h"
#include "raylib.h"
#include "raymath.h"

using namespace std;

bool EndVisualizingInitialAVLTree = false;
vector <VisualizedTree*> InitialVisualizedNodes;

void CreateInitialVisualizedAVLTree(VisualizedTree* AVLTree) {
    queue <VisualizedTree*> q;

    q.push(AVLTree);

    while (!q.empty()) {
        VisualizedTree* node = q.front();
        q.pop();

        InitialVisualizedNodes.push_back(node);

        if (node->left) q.push(node->left);
        if (node->right) q.push(node->right);
    }   
}

void DrawinitialAVLTree(void) {
    static float timer = 0.0f;
    static bool started = false;
    static float duration = 1.0f;
    static int CurrentNode = 0;

    static Vector2 startNodePos;
    static Vector2 endEdgePos;

    for (int i = 0; i < min(CurrentNode, (int)InitialVisualizedNodes.size()); i++) {
        VisualizedTree* node = InitialVisualizedNodes[i];

        DrawRing(node->node.targetPos, node->node.radius - node->node.thickness, node->node.radius, 0.0f, 360.0f, 100, node->node.color);
        DrawShorterLineStartEnd(node->edge.targetStart, node->edge.targetEnd, 50.0f, node->edge.thickness, node->edge.color);
        DrawTextEx(GetFontDefault(), to_string(node->data).c_str(), Vector2Subtract(node->node.targetPos, MeasureTextEx(GetFontDefault(), to_string(node->data).c_str(), 30, 5) / 2), 30, 5, BLACK);
    }

    if (CurrentNode >= InitialVisualizedNodes.size()) return;

    VisualizedTree* node = InitialVisualizedNodes[CurrentNode];

    if (!started) {
        timer = 0.0f;
        started = true;

        startNodePos = InitialVisualizedNodes[CurrentNode]->node.pos;
        endEdgePos = InitialVisualizedNodes[CurrentNode]->edge.end;
    }

    timer += GetFrameTime();

    float Time = timer / duration;
    Time = Clamp(Time, 0.0f, 1.0f);

    node->node.pos = Vector2Lerp(startNodePos, node->node.targetPos, Time);
    node->edge.end = Vector2Lerp(endEdgePos, node->edge.targetEnd, Time);

    DrawRing(node->node.pos, node->node.radius - node->node.thickness, node->node.radius, 0.0f, 360.0f, 100, node->node.color);
    DrawShorterLineStartEnd(node->edge.start, node->node.pos, 50.0f, node->edge.thickness, node->edge.color);
    DrawTextEx(GetFontDefault(), to_string(node->data).c_str(), Vector2Subtract(node->node.pos, MeasureTextEx(GetFontDefault(), to_string(node->data).c_str(), 30, 3) / 2), 30, 3, BLACK);

    if (timer >= duration) {
        node->node.pos = node->node.targetPos;
        node->edge.end = node->edge.targetEnd;

        CurrentNode++;
        started = false;

        if (CurrentNode >= InitialVisualizedNodes.size()) {
            EndVisualizingInitialAVLTree = true;
        }
    }
}

void DeployInitialAVLTreeScene(void) {
    if (InitialVisualizedNodes.size() == 0) {
        CreateAVLTreeScene();

        VisualizedTree* VisualizedAVLTree = AVLTreeState.back();

        CreateInitialVisualizedAVLTree(VisualizedAVLTree);
    }   

    DrawinitialAVLTree();

    if (EndVisualizingInitialAVLTree) {
        AVLTreeScene.push_back(AVLTreeState.back());
        AVLTreeState.clear();
        RotateState.clear();
    }
}