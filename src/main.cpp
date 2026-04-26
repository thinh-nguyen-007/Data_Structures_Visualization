#include <iostream>
#include "raylib.h"
#include "raymath.h"
#include "SceneManager.h"
#include "ModifyScreenScale.h"
#include "Textures.h"
#include "SnapShots.h"
#include "DrawText.h"
#include "DrawPicture.h"
#include "MyColors.h"
#include "StartingScene.h"
#include "ChooseDataScene.h"

using namespace std;

int main() {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(800, 600, "App");
    MaximizeWindow();

    SetTargetFPS(60);

    LoadTextures();
    LoadSnapShots();

    SceneManager Scene;

    RenderTexture2D temp = LoadRenderTexture(ChooseDataScenes[0][0].texture.width, ChooseDataScenes[0][0].texture.height);

    while (!WindowShouldClose()) {

        BeginDrawing();
        ClearBackground(RAYWHITE);

        Scene.ScreenDeployment();

        // DrawTextureRec(ChooseDataScenes[0][0].texture, (Rectangle){0, 0, ChooseDataScenes[0][0].texture.width, -ChooseDataScenes[0][0].texture.height}, (Vector2){0, 0}, WHITE);
        // DrawTextureRec(ChooseDataScenes[0].back().texture, (Rectangle){0, 0, ChooseDataScenes[0].back().texture.width, -ChooseDataScenes[0].back().texture.height}, (Vector2){0, 0}, WHITE);
        // DrawTextureRec(temp.texture, (Rectangle){0, 0, temp.texture.width, -temp.texture.height}, (Vector2){0, 0}, WHITE);
        // DrawTextureRec(StartingScenes[1].texture, (Rectangle){0, 0, StartingScenes[1].texture.width, -StartingScenes[1].texture.height}, (Vector2){0, 0}, WHITE);
        
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

    UnloadTextures();
    UnloadSnapShots();

    CloseWindow();

    return 0;
}