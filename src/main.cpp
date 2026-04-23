#include <iostream>
#include <vector>
#include <cstdint>
#include <string>
#include "AVLTree.h"
#include "VisualizeAVLTree.h"
#include "snapshots.h"
#include "raylib.h"
#include "raymath.h"

using namespace std;

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

    vector <long long> a = {10, 20, 30, 40, 50, 25};
    Tree.Initialize(a);

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(800, 600, "App");
    MaximizeWindow();

    SetTargetFPS(60);

    LoadSnapshots();

    while (!WindowShouldClose()) {
        ClearBackground(RAYWHITE);

        BeginDrawing();

        DrawTextureRec(AVLTreeScenes[0][0].texture, Rectangle{0, 0, (float)AVLTreeScenes[0][0].texture.width, (float)-AVLTreeScenes[0][0].texture.height}, Vector2{0, 0}, WHITE);

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