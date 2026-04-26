#include <iostream>
#include <vector>
#include "raylib.h"
#include "raymath.h"
#include "Textures.h"
#include "DrawText.h"
#include "DrawPicture.h"
#include "MyColors.h"
#include "StartingScene.h"

using namespace std;

float RectangleWidth = 600;
float RectangleHeight = 197;    


vector <RenderTexture2D> StartingScenes;
RenderTexture test;

void StartingSceneInit(void) {
    RenderTexture2D temp = LoadRenderTexture(1.0f * GetScreenWidth(), 1.0f * GetScreenHeight());

    for (int i = 1; i <= 3; i++) {
        StartingScenes.emplace_back(LoadRenderTexture(1.0f * GetScreenWidth(), 1.0f * GetScreenHeight()));
    }

    BeginTextureMode(StartingScenes[0]);
        ClearBackground(RAYWHITE);

        DrawPicture(Background, (Vector2){0, 0}, 0.0f, 1.0f * GetScreenWidth() / (float)Background.width, WHITE);

        DrawGlowText(MyFont, "DATA STRUCTURE VISUALIZATION", (Vector2){(GetScreenWidth() - MeasureTextEx(MyFont, "DATA STRUCTURE VISUALIZATION", 95, 10).x) / 2, (300 - MeasureTextEx(MyFont, "DATA STRUCTURE VISUALIZATION", 95, 10).y) / 2}, 95, 10, Fade(neonYellow, 100.0f), Fade(neonPurple, 100.0f));

        DrawRectangleRounded((Rectangle){200, 300, RectangleWidth, RectangleHeight}, 0.3f, 20, Fade(SKYBLUE, 0.8f));
        DrawRectangleRounded((Rectangle){200, 647, RectangleWidth, RectangleHeight}, 0.3f, 20, Fade(SKYBLUE, 0.8f));
    
        Vector2 TextSize1 = MeasureTextEx(MyFont, "START", 70, 10);
        DrawTextEx(MyFont, "START", Vector2(200 + (RectangleWidth - TextSize1.x) / 2, 300 + (RectangleHeight - TextSize1.y) / 2), 70, 10, BLACK);

        Vector2 TextSize2 = MeasureTextEx(MyFont, "SETTINGS", 70, 10);
        DrawTextEx(MyFont, "SETTINGS", Vector2(200 + (RectangleWidth - TextSize2.x) / 2, 647 + (RectangleHeight - TextSize2.y) / 2), 70, 10, BLACK);
    EndTextureMode();

    StartingScenes[1] = LoadRenderTexture(StartingScenes[0].texture.width, StartingScenes[0].texture.height);
    StartingScenes[2] = LoadRenderTexture(StartingScenes[0].texture.width, StartingScenes[0].texture.height);

    BeginTextureMode(StartingScenes[1]);
        DrawRectangleRoundedLinesEx((Rectangle){200, 300, RectangleWidth, RectangleHeight}, 0.3f, 20, 3, Fade(GlowWhite, 5.0f));
        DrawTextEx(MyFont, "START", Vector2(200 + (RectangleWidth - TextSize1.x) / 2, 300 + (RectangleHeight - TextSize1.y) / 2), 70, 10, Fade(GlowWhite, 5.0f));
    EndTextureMode();

    BeginTextureMode(StartingScenes[2]);
        DrawRectangleRoundedLinesEx((Rectangle){200, 647, RectangleWidth, RectangleHeight}, 0.3f, 20, 3, Fade(GlowWhite, 5.0f));
        DrawTextEx(MyFont, "SETTINGS", Vector2(200 + (RectangleWidth - TextSize2.x) / 2, 647 + (RectangleHeight - TextSize2.y) / 2), 70, 10, Fade(GlowWhite, 5.0f));
    EndTextureMode();
}

void UnloadStartingScene(void) {
    for (int i = 0; i < StartingScenes.size(); i++) {
        UnloadRenderTexture(StartingScenes[i]);
    }
}