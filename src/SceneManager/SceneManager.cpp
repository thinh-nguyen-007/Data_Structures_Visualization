#include <iostream>
#include <vector>
#include <string>
#include <cstdint>
#include "SceneManager.h"
#include "ModifyScreenScale.h"
#include "raymath.h"
#include "raylib.h"
#include "MyColors.h"
#include "Textures.h"
#include "DrawText.h"
#include "DrawPicture.h"
#include "StartingScene.h"
#include "ChooseDataScene.h"

using namespace std;

Vector2 mousePos;
float timer = 0;
int scenex = 0, sceney = 0;

void SceneManager::StartingScene(void) {
    ClearBackground(RAYWHITE);

    DrawTextureRec(StartingScenes[0].texture, (Rectangle){0, 0, ScreenWidth, -ScreenHeight}, (Vector2){0, 0}, WHITE);

    mousePos = GetMousePosition();

    if (mousePos.x >= 200 && mousePos.x <= RectangleWidth + 199 && mousePos.y >= 300 && mousePos.y <= RectangleHeight + 299) {
        DrawTextureRec(StartingScenes[1].texture, (Rectangle){0, 0, ScreenWidth, -ScreenHeight}, (Vector2){0, 0}, WHITE);

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            UpdateSceneNumber(1);
            return;
        }
    }

    if (mousePos.x >= 200 && mousePos.x <= RectangleWidth + 199 && mousePos.y >= 647 && mousePos.y <= RectangleHeight + 646) {
        DrawTextureRec(StartingScenes[2].texture, (Rectangle){0, 0, ScreenWidth, -ScreenHeight}, (Vector2){0, 0}, WHITE);

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            UpdateSceneNumber(2);
            return;
        }
    }   
}

void SceneManager::ChooseDataScene(void) {
    ClearBackground(RAYWHITE);

    DrawTextureRec(ChooseDataScenes[scenex].front().texture, (Rectangle){0, 0, ScreenWidth, -ScreenHeight}, (Vector2){0, 0}, WHITE);

    timer += GetFrameTime();

    if (timer > 0.0001f && sceney < ChooseDataScenes[scenex].size()) {
        timer = 0;
        sceney++;
    }
   
    if (sceney < ChooseDataScenes[scenex].size()) {
        DrawTextureRec(ChooseDataScenes[scenex][sceney].texture, (Rectangle){0, 0, ScreenWidth, -ScreenHeight}, (Vector2){0, 0}, WHITE);
    }
    else { 
        DrawTextureRec(ChooseDataScenes[scenex].back().texture, (Rectangle){0, 0, ScreenWidth, -ScreenHeight}, (Vector2){0, 0}, WHITE);
    }

    mousePos = GetMousePosition();

    if (mousePos.x >= 100 && mousePos.x <= 599 && mousePos.y >= 200 && mousePos.y <= 349) {
        DrawRectangleLinesEx((Rectangle){100, 200, 500, 153}, 6, Fade(neonOrange, 100.0f));     
        
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            scenex = 1;
            sceney = 0;
        }
    }

    if (mousePos.x >= 100 && mousePos.x <= 599 && mousePos.y >= 350 && mousePos.y <= 499) {
        DrawRectangleLinesEx((Rectangle){100, 347, 500, 156}, 6, Fade(neonOrange, 100.0f));

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            scenex = 2;
            sceney = 0;
        }
    }

    if (mousePos.x >= 100 && mousePos.x <= 599 && mousePos.y >= 500 && mousePos.y <= 649) {
        DrawRectangleLinesEx((Rectangle){100, 497, 500, 156}, 6, Fade(neonOrange, 100.0f));

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            scenex = 3;
            sceney = 0;
        }
    }
        
    if (mousePos.x >= 100 && mousePos.x <= 599 && mousePos.y >= 650 && mousePos.y <= 799) {
        DrawRectangleLinesEx((Rectangle){100, 647, 500, 153}, 6, Fade(neonOrange, 100.0f));

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            scenex = 4;
            sceney = 0;
        }
    }

    if (mousePos.x >= 50 && mousePos.x <= 349 && mousePos.y >= 45 + 800 && mousePos.y <= 145 + 800) {
        DrawTextEx(GetFontDefault(), "<", (Vector2){75, 45 + 800 + 5 + (100 - MeasureTextEx(GetFontDefault(), "<", 100, 0).y) / 2}, 100, 0, WHITE);
        DrawTextEx(GetFontDefault(), "-", (Vector2){100, 45 + 800 + 5 + (100 - MeasureTextEx(GetFontDefault(), "-", 100, 0).y) / 2}, 100, 0, WHITE);
        DrawTextEx(GetFontDefault(), "-", (Vector2){120, 45 + 800 + 5 + (100 - MeasureTextEx(GetFontDefault(), "-", 100, 0).y) / 2}, 100, 0, WHITE);
        DrawTextEx(MyFont, "BACK", (Vector2){175, 800 + 45 + (100 - MeasureTextEx(MyFont, "BACK", 50, 0).y) / 2}, 50, 0, WHITE);
        DrawRectangleLinesEx((Rectangle){50, 45 + 800, 300, 100}, 3.0f, Fade(GlowWhite, 100.0f));

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            UpdateSceneNumber(0);
            scenex = 0;
            sceney = 0;
            return;
        }
    }

    if (scenex != 0 && mousePos.x >= 1420 && mousePos.x <= 1870 && mousePos.y >= 45 + 800 && mousePos.y <= 145 + 800) {
        DrawTextEx(GetFontDefault(), ">", (Vector2){1820, 45 + 800 + 5 + (100 - MeasureTextEx(GetFontDefault(), ">", 100, 0).y) / 2}, 100, 0, WHITE);
        DrawTextEx(GetFontDefault(), "-", (Vector2){1785, 45 + 800 + 5 + (100 - MeasureTextEx(GetFontDefault(), "-", 100, 0).y) / 2}, 100, 0, WHITE);
        DrawTextEx(GetFontDefault(), "-", (Vector2){1745, 45 + 800 + 5 + (100 - MeasureTextEx(GetFontDefault(), "-", 100, 0).y) / 2}, 100, 0, WHITE);
        DrawTextEx(MyFont, "CONTINUE", (Vector2){1440, 800 + 45 + (100 - MeasureTextEx(MyFont, "CONTINUE", 50, 0).y) / 2}, 50, 0, WHITE);
        DrawRectangleLinesEx((Rectangle){1420, 45 + 800, 450, 100}, 3.0f, Fade(GlowWhite, 100.0f));

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            UpdateSceneNumber(scenex + 2);
            return;
        }
    }
}

void SceneManager::SettingScene(void) {
    
}

void SceneManager::ScreenDeployment(void) {
    if (GetSceneNumber() == 0)
        StartingScene();
    else if (GetSceneNumber() == 1) 
        ChooseDataScene();
    else if (GetSceneNumber() == 2)
        SettingScene();
}