#include <iostream>
#include <queue>
#include "DrawLastAVLTree.h"
#include "VisualizeAVLTree.h"
#include "DrawObjects.h"
#include "raylib.h"
#include "raymath.h"

using namespace std;

void DrawLastAVLTreeScene(void) {
    VisualizedTree* LastAVLTree = AVLTreeScene.back();

    queue <VisualizedTree*> q;

    q.push(LastAVLTree);

    while (!q.empty()) {
        VisualizedTree* node = q.front();
        q.pop();

        DrawRing(node->node.pos, node->node.radius - node->node.thickness, node->node.radius, 0.0f, 360.0f, 100, node->node.color);
        DrawShorterLineStartEnd(node->edge.start, node->node.pos, 50.0f, node->edge.thickness, node->edge.color);
        DrawTextEx(GetFontDefault(), to_string(node->data).c_str(), Vector2Subtract(node->node.pos, MeasureTextEx(GetFontDefault(), to_string(node->data).c_str(), 30, 3) / 2), 30, 3, BLACK);

        if (node->left) {
            q.push(node->left);
        }

        if (node->right) {
            q.push(node->right);
        }
    }
}