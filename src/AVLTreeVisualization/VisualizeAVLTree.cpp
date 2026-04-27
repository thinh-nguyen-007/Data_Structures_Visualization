#include <iostream>
#include <vector>
#include <cstdint>
#include <string>
#include <queue>
#include "VisualizeAVLTree.h"
#include "AVLTree.h"
#include "DrawObjects.h"
#include "MathFunctions.h"
#include "Items.h"
#include "raylib.h"
#include "raymath.h"

using namespace std;

const float eps = 1e-7f;

namespace {
    Camera2D camera = {0};
    float speed = 0.01f;
}

vector <pair <long long, int> > RotateState;
float totWidth;
float totHeight;
float timer = 0.0f;
int CurrentNode = 0;
VisualizedTree* VisualizedAVLTree = nullptr;
vector <VisualizedTree*> VisualizedNodes;

void ComputeInformation(void) {
    totWidth = Pow(2, Tree.getHeight(Tree.tree) - 1) * 200.0f;
    totHeight = Tree.getHeight(Tree.tree) * 200.0f;
}

void AVLTreeScenesInit(void) {
    ComputeInformation();

    camera.target = {totWidth / 2.0f, 50.0f};
    camera.offset = Vector2{GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f};
    camera.rotation = 0.0f;
    camera.zoom = 0.5f;

    PrepareAVLTree();
}

void AVLTreeScenesDeployment(void) {
    if (IsKeyDown(KEY_UP)) camera.zoom += 0.05f;
    if (IsKeyDown(KEY_DOWN)) camera.zoom -= 0.05f;

    camera.zoom = max(camera.zoom, 0.1f);


    if (CurrentNode < VisualizedNodes.size()) {
        camera.target = VisualizedNodes[CurrentNode]->node.pos;
    }

    if (IsKeyDown(KEY_W)) camera.target.y -= 100;
    if (IsKeyDown(KEY_S)) camera.target.y += 100;
    if (IsKeyDown(KEY_A)) camera.target.x -= 100;
    if (IsKeyDown(KEY_D)) camera.target.x += 100;

    BeginMode2D(camera);
        DrawAVLTree();
    EndMode2D();
}

void PrepareAVLTree(void) {
    if (Tree.tree) {
        VisualizedAVLTree = new VisualizedTree(Tree.tree->data, Vector2{totWidth / 2, 50}, Vector2{totWidth / 2, 50});
        VisualizedAVLTree->edge = line(Vector2{totWidth / 2, 50}, Vector2{totWidth / 2, 50}, Vector2{totWidth / 2, 50}, Vector2{totWidth / 2, 50}, 5.0f, BLACK);
        VisualizedAVLTree->node = circle(Vector2{totWidth / 2, 50}, Vector2{totWidth / 2, 50}, 50.0f, 5.0f, BLACK);
    }

    RecuresiveDraw(Tree.tree, VisualizedAVLTree, Vector2{totWidth / 2, 50}, 50, totWidth / 4, totHeight / (1.0f * Tree.getHeight(Tree.tree) - 1.0f));

    if (VisualizedAVLTree == nullptr) return;

    queue <VisualizedTree*> q;

    q.push(VisualizedAVLTree);

    while (!q.empty()) {
        VisualizedTree* node = q.front();
        q.pop();

        VisualizedNodes.push_back(node);

        if (node->left) q.push(node->left);
        if (node->right) q.push(node->right);
    }
}

void RecuresiveDraw(AVLTree::node* tree, VisualizedTree* visualizedNode, Vector2 parpos, float depth, float spacing, float distance) {
    if (tree == nullptr) return;

    if (tree->left) {
        Vector2 dir = Vector2Normalize(Vector2Subtract(Vector2{parpos.x - spacing, depth + distance}, parpos));

        VisualizedTree *left = new VisualizedTree(tree->left->data, parpos, Vector2{parpos.x - spacing, depth + distance});
        left->edge = line(parpos, parpos, parpos + dir * 100.0f, Vector2{parpos.x - spacing, depth + distance}, 5.0f, BLACK);
        left->node = circle(Vector2{parpos.x - 100, depth + 100}, Vector2{parpos.x - spacing, depth + distance}, 50.0f, 5.0f, BLACK);
        visualizedNode->left = left;
    }

    if (tree->right) {
        Vector2 dir = Vector2Normalize(Vector2Subtract(Vector2{parpos.x + spacing, depth + distance}, parpos));

        VisualizedTree *right = new VisualizedTree(tree->right->data, parpos, Vector2{parpos.x + spacing, depth + distance});
        right->edge = line(parpos, parpos, parpos + dir * 100.0f, Vector2{parpos.x + spacing, depth + distance}, 5.0f, BLACK);
        right->node = circle(Vector2{parpos.x + 100, depth + 100}, Vector2{parpos.x + spacing, depth + distance}, 50.0f, 5.0f, BLACK);
        visualizedNode->right = right;
    }

    if (tree->left)
        RecuresiveDraw(tree->left, visualizedNode->left, Vector2{parpos.x - spacing, depth + distance}, depth + distance, spacing / 2, distance);
    if (tree->right) 
        RecuresiveDraw(tree->right, visualizedNode->right, Vector2{parpos.x + spacing, depth + distance}, depth + distance, spacing / 2, distance);
}  

void DrawAVLTree(void) {
    static float timer = 0.0f;
    static bool started = false;
    static float duration = 1.0f;

    static Vector2 startNodePos;
    static Vector2 endEdgePos;

    for (int i = 0; i < min(CurrentNode, (int)VisualizedNodes.size()); i++) {
        VisualizedTree* node = VisualizedNodes[i];

        DrawRing(node->node.targetPos, node->node.radius - node->node.thickness, node->node.radius, 0.0f, 360.0f, 100, node->node.color);
        DrawShorterLineStartEnd(node->edge.targetStart, node->edge.targetEnd, 50.0f, node->edge.thickness, node->edge.color);
        DrawTextEx(GetFontDefault(), to_string(node->data).c_str(), Vector2Subtract(node->node.targetPos, MeasureTextEx(GetFontDefault(), to_string(node->data).c_str(), 30, 5) / 2), 30, 5, BLACK);
    }

    if (CurrentNode >= VisualizedNodes.size()) return;

    VisualizedTree* node = VisualizedNodes[CurrentNode];

    if (!started) {
        timer = 0.0f;
        started = true;

        startNodePos = VisualizedNodes[CurrentNode]->node.pos;
        endEdgePos = VisualizedNodes[CurrentNode]->edge.end;
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
    }
}

void OutputTree(void) {
    for (int i = 0; i < VisualizedNodes.size(); i++) {
        cout << VisualizedNodes[i]->node.pos.x << " " << VisualizedNodes[i]->node.pos.y;
        cout << " ___ " << VisualizedNodes[i]->node.targetPos.x << " " << VisualizedNodes[i]->node.targetPos.y << endl;
    }
}

void UnloadAVLTreeScenes(void) {
    
}