#include <iostream>
#include <vector>
#include <cstdint>
#include <string>
#include <queue>
#include "VisualizeAVLTree.h"
#include "InsertAVLTreeScene.h"
#include "InitialAVLTreeScene.h"
#include "DrawLastAVLTree.h"
#include "DeleteAVLTreeScene.h"
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

int AVLScene = -1;
/*
0 - Initial AVL Tree Scene
1 - Insert AVL Tree Scene
2 - Delete AVL Tree Scene
3 - Last AVL Tree Scene
*/

vector <pair <long long, int> > RotateState;
float totWidth;
float totHeight;
float timer = 0.0f;
int CurrentNode = 0;
VisualizedTree* VisualizedAVLTree = nullptr;
VisualizedTree* FindNode = nullptr;
vector <VisualizedTree*> VisualizedNodes;
vector <VisualizedTree*> AVLTreeState;
vector <VisualizedTree*> AVLTreeScene;

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
        DrawAllAVLTree();
    EndMode2D();
}

void CreateAVLTreeScene(void) {
    PrepareAVLTree();
    AVLTreeState.push_back(VisualizedAVLTree);
}

void PrepareAVLTree(void) {
    if (Tree.tree) {
        VisualizedAVLTree = new VisualizedTree(Tree.tree->data, Vector2{totWidth / 2, 50}, Vector2{totWidth / 2, 50});
        VisualizedAVLTree->edge = line(Vector2{totWidth / 2, 50}, Vector2{totWidth / 2, 50}, Vector2{totWidth / 2, 50}, Vector2{totWidth / 2, 50}, 5.0f, BLACK);
        VisualizedAVLTree->node = circle(Vector2{totWidth / 2, 50}, Vector2{totWidth / 2, 50}, 50.0f, 5.0f, BLACK);

        RecuresiveDraw(Tree.tree, VisualizedAVLTree, Vector2{totWidth / 2, 50}, 50, totWidth / 4, totHeight / (1.0f * Tree.getHeight(Tree.tree) - 1.0f));
    }

    /*queue <AVLTree::node*> q;

    if (Tree.tree) q.push(Tree.tree);

    while (!q.empty()) {
        AVLTree::node* node = q.front();
        q.pop();

        cout << node->data << " ";

        if (node->left) {
            q.push(node->left);
        }

        if (node->right) {
            q.push(node->right);
        }
    }

    cout << endl;*/

    if (VisualizedAVLTree == nullptr) return;
}

void FlattenTheTree(VisualizedTree* AVLTree, vector <VisualizedTree*> &VisualizedNodes, vector <VisualizedTree*> &version2, long long FixedPoint) {
    queue <pair <VisualizedTree*, bool> > q;

    if (AVLTree->data == FixedPoint) {
        q.push(make_pair(AVLTree, true));
    }
    else {
        q.push(make_pair(AVLTree, false));
    }

    while (!q.empty()) {
        VisualizedTree* node = q.front().first;
        bool Check = q.front().second;
        q.pop();

        if (!Check) {
            VisualizedNodes.push_back(node);
        }
        else {
            version2.push_back(node);
        }

        if (node->left) {
            if (node->left->data == FixedPoint) {
                q.push(make_pair(node->left, true));
            }
           else {
                q.push(make_pair(node->left, Check));
           }
        }

        if (node->right) {
            if (node->right->data == FixedPoint) {
                q.push(make_pair(node->right, true));
            }
            else {
                q.push(make_pair(node->right, Check));
            }
        }
    }
}

void RecuresiveDraw(AVLTree::node* tree, VisualizedTree* visualizedNode, Vector2 parpos, float depth, float spacing, float distance) {
    if (tree == nullptr) return;

    if (tree->data == RotateState.front().first && FindNode == nullptr) {
        FindNode = new VisualizedTree(*visualizedNode);
    }

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

void DrawAllAVLTree(void) {

}

void OutputTree(void) {
    for (int i = 0; i < VisualizedNodes.size(); i++) {
        cout << VisualizedNodes[i]->node.pos.x << " " << VisualizedNodes[i]->node.pos.y;
        cout << " ___ " << VisualizedNodes[i]->node.targetPos.x << " " << VisualizedNodes[i]->node.targetPos.y << endl;
    }
}

void UpdateAVLTreeSceneNumber(int x) {
    if (x != -1) 
        AVLScene = x;
}

void DeployAVLTreeVisualization(void) {
    if (AVLScene == 0) {
        DeployInitialAVLTreeScene();

        if (AVLTreeState.size() == 0) {
            UpdateAVLTreeSceneNumber(3);
        }
    }
    else if (AVLScene == 1) {
        DrawInsertAVLTreeScene();

        if (AVLTreeState.size() == 0) {
            UpdateAVLTreeSceneNumber(3);
        }
    }
    else if (AVLScene == 2) {
        DrawDeleteAVLTreeScene();

        if (AVLTreeState.size() == 0) {
            UpdateAVLTreeSceneNumber(3);
        }
    }
    else if (AVLScene == 3) {
        DrawLastAVLTreeScene();
    }
}

void UnloadAVLTreeScenes(void) {
    
}

int GetAVLTreeSceneNumber(void) {
    return AVLScene;
}