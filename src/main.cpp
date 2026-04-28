#include <iostream>
#include <vector>
#include <cstdint>
#include <string>
#include <random>
#include <chrono>
#include <queue>
#include "AVLTree.h"
#include "VisualizeAVLTree.h"
#include "InsertAVLTreeSCene.h"
#include "InitialAVLTreeScene.h"
#include "DrawLastAVLTree.h"
#include "snapshots.h"
#include "MathFunctions.h"
#include "raylib.h"
#include "raymath.h"
#include "DrawObjects.h"

using namespace std;

struct DATA {
    Vector2 pos;
    Vector2 targetPos;
} node;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int rnd(int l, int r) {
    // return uniform_int_distribution<int>(l, r)(rng);

    return (l + rng() % (r - l + 1));
}

int main() {
    // int n;
    // cin >> n;
    // vector <long long> a(n);

    // for (int i = 0; i < n; i++) 
    //     cin >> a[i];

    // Tree.Initialize(a);
    // a = Tree.LevelOrder();

    // for (int i = 0; i < a.size(); i++) 
    //     cout << a[i] << " ";

    int n = 3;
    vector <long long> a;
    
    for (int i = 1; i <= 1000; i++) 
        a.push_back(i);

    shuffle(a.begin(), a.end(), rng);
    a.resize(n);

    Tree.Initialize(a);

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(800, 600, "App");
    MaximizeWindow();

    SetTargetFPS(60);

    LoadSnapshots();

    node.pos = Vector2{100, 100};
    node.targetPos = Vector2{200, 200};

    Vector2 start = node.pos;
    Vector2 end = node.targetPos;
    Vector2 newStart = start + Vector2{1, 1} * 100;
    Vector2 newEnd = end + Vector2{1, 1} * 100;
    Vector2 dir = Vector2Normalize(Vector2Subtract(newStart, start));

    // queue <AVLTree::node*> q;

    // if (Tree.tree) {
    //     q.push(Tree.tree);
    // }

    // while (!q.empty()) {
    //     AVLTree::node* node = q.front();
    //     q.pop();

    //     cout << node->data << " ";

    //     if (node->left) {
    //         q.push(node->left);
    //     }

    //     if (node->right) {
    //         q.push(node->right);
    //     }
    // }

    // cout << endl;

    /*if (AVLTreeState[0] == nullptr) cout << -1 << endl;   
    
    for (int i = 0; i < RotateState.size(); i++) {
        cout << RotateState[i].first << " " << RotateState[i].second << endl;
    }*/

    // OutputTree();

    // for (int i = 0; i < a.size(); i++) {
    //     cout << a[i] << " ";
    // }

    // cout << endl;

    // Tree.Insert(Tree.tree, 1000);

    // cout << AVLTreeState.size() << endl;

    // queue <AVLTree::node*> q;

    // if (Tree.tree) {
    //     q.push(Tree.tree);
    // }

    // while (!q.empty()) {
    //     AVLTree::node* node = q.front();
    //     q.pop();

    //     cout << node->data << " ";

    //     if (node->left) {
    //         q.push(node->left);
    //     }
        
    //     if (node->right) {
    //         q.push(node->right);
    //     }
    // }

    // cout << endl;

    bool DoInsert = true;

    // DeployInitialAVLTreeScene();

    while (!WindowShouldClose()) {

        BeginDrawing();

        ClearBackground(RAYWHITE);

        DeployInitialAVLTreeScene();

        // if (DoInsert) {
        //     DoInsert = false;

        //     Tree.Insert(Tree.tree, 1000);
        // }

        // DrawInsertAVLTreeScene();

        // DrawLastAVLTreeScene();

        // DrawTextureRec(AVLTreeScenes[0][0].texture, Rectangle{0, 0, (float)AVLTreeScenes[0][0].texture.width, (float)-AVLTreeScenes[0][0].texture.height}, Vector2{0, 0}, WHITE);

        // AVLTreeScenesDeployment();

        // start = Vector2Lerp(start, newStart, 0.07f);
        // end = Vector2Lerp(end, newEnd, 0.07f);

        // DrawShorterLineStartEnd(start, end, 50.0f, 5.0f, BLACK);

        // if (start == newStart && end == newEnd) {
        //     DrawRectangle(GetScreenWidth() / 2 - 50, GetScreenHeight() / 2 - 50, 100, 100, RED);
        // }

        EndDrawing();
    }


    //MAKING A TEXT APPEAR SLIGHTLY SLOWER THAN NORMAL

    // string text = "Hello, world!";
    // int visibleChars = 0;
    // float timer = 0;

    // while (!WindowShouldClose())
    // {
    //     timer += GetFrameTime();

    //     if (timer > 0.08f && visibleChars < text.size())
    //     {
    //         visibleChars++;
    //         timer = 0;
    //     }

    //     BeginDrawing();
    //     ClearBackground(BLACK);

    //     DrawText(text.substr(0, visibleChars).c_str(), 100, 200, 30, WHITE);

    //     EndDrawing();
    // }

    UnloadSnapshots();

    CloseWindow();

    return 0;
}