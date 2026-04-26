#include <iostream>
#include <vector>
#include <string>
#include "raylib.h"
#include "raymath.h"
#include "Textures.h"
#include "DrawText.h"
#include "DrawPicture.h"
#include "MyColors.h"
#include "ChooseDataScene.h"

using namespace std;

namespace {
    float ScreenWidth = GetScreenWidth();
    float ScreenHeight = GetScreenHeight();
}

vector <vector <RenderTexture2D> > ChooseDataScenes;
RenderTexture2D DrawnText;

void PreviewDataSceneInit(void) {
    string Introducing = "This project is a collaborative data structure visualization system developed by group 02 with the goal of making data structures easier to learn and understand. The system uses interactive animations to demonstrate how common data structures including heap, linked list, AVL tree and graph operate through actions consisting of insertion, deletion, searching, and traversal. Each member contributed to different aspects of the project, including design, programming, algorithm implementation, and testing. By combining teamwork and technical knowledge, the group created an educational tool that helps users observe data structure behavior step by step in a clear and engaging way.";
    string Title = "Introduction";
    vector <string> IntroducingLines;
    DrawnText = LoadRenderTexture(1.0f * GetScreenWidth(), 1.0f * GetScreenHeight());

    BeginTextureMode(DrawnText);
        ClearBackground(BLANK);
    EndTextureMode();

    float TitleStartingPoint;

    for (int i = 0; i < Title.size(); i++) {
        ChooseDataScenes[0].emplace_back(LoadRenderTexture(ChooseDataScenes[0].front().texture.width, ChooseDataScenes[0].front().texture.height));

        BeginTextureMode(DrawnText);
            DrawTextEx(MyFont, Title.substr(0, i + 1).c_str(), (Vector2){(1220 - MeasureTextEx(MyFont, "Introduction", 35, 0).x) / 2 + 600, (60 - MeasureTextEx(MyFont, "Introduction", 35, 0).y) / 2 + 200}, 35, 0, Fade(neonYellow, 100.0f));
        EndTextureMode();

        BeginTextureMode(ChooseDataScenes[0].back());
            DrawTextureRec(ChooseDataScenes[0].front().texture, (Rectangle){0, 0, ChooseDataScenes[0].front().texture.width, -ChooseDataScenes[0].front().texture.height}, (Vector2){0, 0}, WHITE);

            DrawTextureRec(DrawnText.texture, (Rectangle){0, 0, DrawnText.texture.width, -DrawnText.texture.height}, (Vector2){0, 0}, WHITE);
        EndTextureMode();
    }

    int AvgLineLength = Introducing.size() / 11;
    Introducing = Introducing + " ";

    int i = 0;

    while (i < Introducing.size()) {
        int LineEnd = Introducing.find(" ", i + AvgLineLength);

        if (LineEnd == -1) {
            LineEnd = Introducing.size() - 1;
        }

        IntroducingLines.push_back(Introducing.substr(i, LineEnd - i));
        i = LineEnd + 1;
    }

    for (int i = 0; i < IntroducingLines.size(); i++) {
        for (int j = 0; j < IntroducingLines[i].size(); j++) {
            ChooseDataScenes[0].emplace_back(LoadRenderTexture(ChooseDataScenes[0].front().texture.width, ChooseDataScenes[0].front().texture.height));

            BeginTextureMode(DrawnText);
                DrawTextEx(MyFont, IntroducingLines[i].substr(0, j + 1).c_str(), Vector2(700, 260 + i * 30), 27, 0, Fade(neonYellow, 100.0f));
            EndTextureMode();

            BeginTextureMode(ChooseDataScenes[0].back());
                DrawTextureRec(ChooseDataScenes[0].front().texture, (Rectangle){0, 0, ChooseDataScenes[0].front().texture.width, -ChooseDataScenes[0].front().texture.height}, (Vector2){0, 0}, WHITE);
                
                DrawTextureRec(DrawnText.texture, (Rectangle){0, 0, DrawnText.texture.width, -DrawnText.texture.height}, (Vector2){0, 0}, WHITE);
            EndTextureMode();
        }       
    }

    Title = "Group members";
    string member[2];
    member[0] = "25125026 - Le Phan Duc Man                 25125066 - Nguyen Quoc Thinh";
    member[1] = "25125073 - Nguyen Xuan Gia Khang      25125079 - Nguyen Quoc Bao  ";

    for (int i = 0; i < Title.size(); i++) {
        ChooseDataScenes[0].emplace_back(LoadRenderTexture(ChooseDataScenes[0].front().texture.width, ChooseDataScenes[0].front().texture.height));

        BeginTextureMode(DrawnText);
            DrawTextEx(MyFont, Title.substr(0, i + 1).c_str(), (Vector2){(1220 - MeasureTextEx(MyFont, "Group members", 35, 0).x) / 2 + 600, (60 - MeasureTextEx(MyFont, "Group members", 35, 0).y) / 2 + 590}, 35, 0, Fade(neonYellow, 100.0f));
        EndTextureMode();

        BeginTextureMode(ChooseDataScenes[0].back());
            DrawTextureRec(ChooseDataScenes[0].front().texture, (Rectangle){0, 0, ChooseDataScenes[0].front().texture.width, -ChooseDataScenes[0].front().texture.height}, (Vector2){0, 0}, WHITE);

            DrawTextureRec(DrawnText.texture, (Rectangle){0, 0, DrawnText.texture.width, -DrawnText.texture.height}, (Vector2){0, 0}, WHITE);
        EndTextureMode();
    }

    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j < member[i].size(); j++) {
            ChooseDataScenes[0].emplace_back(LoadRenderTexture(ChooseDataScenes[0].front().texture.width, ChooseDataScenes[0].front().texture.height));

            BeginTextureMode(DrawnText);
                DrawTextEx(MyFont, member[i].substr(0, j + 1).c_str(), (Vector2){700, 650 + i * 30}, 27, 0, Fade(neonYellow, 100.0f));
            EndTextureMode();

            BeginTextureMode(ChooseDataScenes[0].back());
                DrawTextureRec(ChooseDataScenes[0].front().texture, (Rectangle){0, 0, ChooseDataScenes[0].front().texture.width, -ChooseDataScenes[0].front().texture.height}, (Vector2){0, 0}, WHITE);

                DrawTextureRec(DrawnText.texture, (Rectangle){0, 0, DrawnText.texture.width, -DrawnText.texture.height}, (Vector2){0, 0}, WHITE);
            EndTextureMode();
        }
    }
}   

void HeapDataSceneInit() {
    
}

void LinkedListDataSceneInit() {

}

void AVLTreeDataSceneInit() {

}

void GraphDataSceneInit() {

}

void ChooseDataSceneInit(void) {
    RenderTexture2D temp = LoadRenderTexture(1.0f * GetScreenWidth(), 1.0f * GetScreenHeight());

    float ScreenWidth = GetScreenWidth();
    float ScreenHeight = GetScreenHeight();

    for (int i = 1; i <= 5; i++) {
        vector <RenderTexture2D> temp;

        temp.emplace_back(LoadRenderTexture(1.0f * GetScreenWidth(), 1.0f * GetScreenHeight()));

        ChooseDataScenes.emplace_back(temp);
    }

    BeginTextureMode(ChooseDataScenes[0][0]);
        ClearBackground(myDarkGray);

        DrawPicture(Background, (Vector2){0, 0}, 0.0f, 1.0f * GetScreenWidth() / (float)Background.width, WHITE);

        DrawRectangleRec((Rectangle){600, 200, 1220, 600}, Fade(SKYBLUE, 0.8f));

        DrawRectangleRec((Rectangle){100, 200, 500, 150}, Fade(SKYBLUE, 0.8f));
        DrawRectangleRec((Rectangle){100, 350, 500, 150}, Fade(SKYBLUE, 0.8f));
        DrawRectangleRec((Rectangle){100, 500, 500, 150}, Fade(SKYBLUE, 0.8f));
        DrawRectangleRec((Rectangle){100, 650, 500, 150}, Fade(SKYBLUE, 0.8f));

        DrawRectangleRec((Rectangle){50, 45 + 800, 300, 100}, Fade(SKYBLUE, 0.8f));

        DrawRectangleLinesEx((Rectangle){100, 200, 500, 150}, 3.0f, Fade(GlowWhite, 100.0f));
        DrawRectangleLinesEx((Rectangle){100, 350, 500, 150}, 3.0f, Fade(GlowWhite, 100.0f));
        DrawRectangleLinesEx((Rectangle){100, 500, 500, 150}, 3.0f, Fade(GlowWhite, 100.0f));
        DrawRectangleLinesEx((Rectangle){100, 650, 500, 150}, 3.0f, Fade(GlowWhite, 100.0f));

        DrawNormalText(MyFont, "HEAP", (Vector2){(500 - MeasureTextEx(MyFont, "HEAP", 50, 10).x) / 2 + 100, (150 - MeasureTextEx(MyFont, "HEAP", 50, 10).y) / 2 + 200}, 50, 10, Fade(WHITE, 100.0f));
        DrawNormalText(MyFont, "LINKED LIST", (Vector2){(500 - MeasureTextEx(MyFont, "LINKED LIST", 50, 10).x) / 2 + 100, (150 - MeasureTextEx(MyFont, "LINKED LIST", 50, 10).y) / 2 + 350}, 50, 10, Fade(WHITE, 100.0f));
        DrawNormalText(MyFont, "AVL TREE", (Vector2){(500 - MeasureTextEx(MyFont, "AVL TREE", 50, 10).x) / 2 + 100, (150 - MeasureTextEx(MyFont, "AVL TREE", 50, 10).y) / 2 + 500}, 50, 10, Fade(WHITE, 100.0f));
        DrawNormalText(MyFont, "GRAPH", (Vector2){(500 - MeasureTextEx(MyFont, "GRAPH", 50, 10).x) / 2 + 100, (150 - MeasureTextEx(MyFont, "GRAPH", 50, 10).y) / 2 + 650}, 50, 10, Fade(WHITE, 100.0f));

        DrawTextEx(GetFontDefault(), "<", (Vector2){75, 45 + 800 + 5 + (100 - MeasureTextEx(GetFontDefault(), "<", 100, 0).y) / 2}, 100, 0, BLACK);
        DrawTextEx(GetFontDefault(), "-", (Vector2){100, 45 + 800 + 5 + (100 - MeasureTextEx(GetFontDefault(), "-", 100, 0).y) / 2}, 100, 0, BLACK);
        DrawTextEx(GetFontDefault(), "-", (Vector2){120, 45 + 800 + 5 + (100 - MeasureTextEx(GetFontDefault(), "-", 100, 0).y) / 2}, 100, 0, BLACK);
        DrawTextEx(MyFont, "BACK", (Vector2){175, 800 + 45 + (100 - MeasureTextEx(MyFont, "BACK", 50, 0).y) / 2}, 50, 0, BLACK);

        DrawGlowText(MyFont, "CHOOSE DATA STRUCTURE", (Vector2){(ScreenWidth - MeasureTextEx(MyFont, "CHOOSE DATA STRUCTURE", 100, 30).x) / 2, (200 - MeasureTextEx(MyFont, "CHOOSE DATA STRUCTURE", 100, 30).y) / 2}, 100, 30, Fade(DARKBLUE, 0.8f), Fade(neonPurple, 100.0f));
        

    EndTextureMode();

    PreviewDataSceneInit();

    ChooseDataScenes[1][0] = LoadRenderTexture(ChooseDataScenes[0][0].texture.width, ChooseDataScenes[0][0].texture.height);
    ChooseDataScenes[2][0] = LoadRenderTexture(ChooseDataScenes[0][0].texture.width, ChooseDataScenes[0][0].texture.height);
    ChooseDataScenes[3][0] = LoadRenderTexture(ChooseDataScenes[0][0].texture.width, ChooseDataScenes[0][0].texture.height);
    ChooseDataScenes[4][0] = LoadRenderTexture(ChooseDataScenes[0][0].texture.width, ChooseDataScenes[0][0].texture.height);

    BeginTextureMode(ChooseDataScenes[1][0]);
        DrawTextureRec(ChooseDataScenes[0].front().texture, (Rectangle){0, 0, ChooseDataScenes[0].front().texture.width, -ChooseDataScenes[0].front().texture.height}, (Vector2){0, 0}, WHITE);

        DrawTextureRec(DrawnText.texture, (Rectangle){0, 0, DrawnText.texture.width, -DrawnText.texture.height}, (Vector2){0, 0}, WHITE);

        DrawRectangleLinesEx((Rectangle){100, 200, 500, 153}, 6, Fade(neonOrange, 100.0f));       
        
        DrawRectangleRec((Rectangle){1420, 45 + 800, 450, 100}, Fade(SKYBLUE, 0.8f));

        DrawTextEx(GetFontDefault(), ">", (Vector2){1820, 45 + 800 + 5 + (100 - MeasureTextEx(GetFontDefault(), ">", 100, 0).y) / 2}, 100, 0, BLACK);
        DrawTextEx(GetFontDefault(), "-", (Vector2){1785, 45 + 800 + 5 + (100 - MeasureTextEx(GetFontDefault(), "-", 100, 0).y) / 2}, 100, 0, BLACK);
        DrawTextEx(GetFontDefault(), "-", (Vector2){1745, 45 + 800 + 5 + (100 - MeasureTextEx(GetFontDefault(), "-", 100, 0).y) / 2}, 100, 0, BLACK);
        DrawTextEx(MyFont, "CONTINUE", (Vector2){1440, 800 + 45 + (100 - MeasureTextEx(MyFont, "CONTINUE", 50, 0).y) / 2}, 50, 0, BLACK);
    EndTextureMode();

    BeginTextureMode(ChooseDataScenes[2][0]);
        DrawTextureRec(ChooseDataScenes[0].front().texture, (Rectangle){0, 0, ChooseDataScenes[0].front().texture.width, -ChooseDataScenes[0].front().texture.height}, (Vector2){0, 0}, WHITE);

        DrawTextureRec(DrawnText.texture, (Rectangle){0, 0, DrawnText.texture.width, -DrawnText.texture.height}, (Vector2){0, 0}, WHITE);

        DrawRectangleLinesEx((Rectangle){100, 347, 500, 156}, 6, Fade(neonOrange, 100.0f));

        DrawRectangleRec((Rectangle){1420, 45 + 800, 450, 100}, Fade(SKYBLUE, 0.8f));

        DrawTextEx(GetFontDefault(), ">", (Vector2){1820, 45 + 800 + 5 + (100 - MeasureTextEx(GetFontDefault(), ">", 100, 0).y) / 2}, 100, 0, BLACK);
        DrawTextEx(GetFontDefault(), "-", (Vector2){1785, 45 + 800 + 5 + (100 - MeasureTextEx(GetFontDefault(), "-", 100, 0).y) / 2}, 100, 0, BLACK);
        DrawTextEx(GetFontDefault(), "-", (Vector2){1745, 45 + 800 + 5 + (100 - MeasureTextEx(GetFontDefault(), "-", 100, 0).y) / 2}, 100, 0, BLACK);
        DrawTextEx(MyFont, "CONTINUE", (Vector2){1440, 800 + 45 + (100 - MeasureTextEx(MyFont, "CONTINUE", 50, 0).y) / 2}, 50, 0, BLACK);
    EndTextureMode();

    BeginTextureMode(ChooseDataScenes[3][0]);
        DrawTextureRec(ChooseDataScenes[0].front().texture, (Rectangle){0, 0, ChooseDataScenes[0].front().texture.width, -ChooseDataScenes[0].front().texture.height}, (Vector2){0, 0}, WHITE);

        DrawTextureRec(DrawnText.texture, (Rectangle){0, 0, DrawnText.texture.width, -DrawnText.texture.height}, (Vector2){0, 0}, WHITE);

        DrawRectangleLinesEx((Rectangle){100, 497, 500, 156}, 6, Fade(neonOrange, 100.0f));

        DrawRectangleRec((Rectangle){1420, 45 + 800, 450, 100}, Fade(SKYBLUE, 0.8f));

        DrawTextEx(GetFontDefault(), ">", (Vector2){1820, 45 + 800 + 5 + (100 - MeasureTextEx(GetFontDefault(), ">", 100, 0).y) / 2}, 100, 0, BLACK);
        DrawTextEx(GetFontDefault(), "-", (Vector2){1785, 45 + 800 + 5 + (100 - MeasureTextEx(GetFontDefault(), "-", 100, 0).y) / 2}, 100, 0, BLACK);
        DrawTextEx(GetFontDefault(), "-", (Vector2){1745, 45 + 800 + 5 + (100 - MeasureTextEx(GetFontDefault(), "-", 100, 0).y) / 2}, 100, 0, BLACK);
        DrawTextEx(MyFont, "CONTINUE", (Vector2){1440, 800 + 45 + (100 - MeasureTextEx(MyFont, "CONTINUE", 50, 0).y) / 2}, 50, 0, BLACK);
    EndTextureMode();

    BeginTextureMode(ChooseDataScenes[4][0]);
        DrawTextureRec(ChooseDataScenes[0].front().texture, (Rectangle){0, 0, ChooseDataScenes[0].front().texture.width, -ChooseDataScenes[0].front().texture.height}, (Vector2){0, 0}, WHITE);

        DrawTextureRec(DrawnText.texture, (Rectangle){0, 0, DrawnText.texture.width, -DrawnText.texture.height}, (Vector2){0, 0}, WHITE);

        DrawRectangleLinesEx((Rectangle){100, 647, 500, 153}, 6, Fade(neonOrange, 100.0f));

        DrawRectangleRec((Rectangle){1420, 45 + 800, 450, 100}, Fade(SKYBLUE, 0.8f));

        DrawTextEx(GetFontDefault(), ">", (Vector2){1820, 45 + 800 + 5 + (100 - MeasureTextEx(GetFontDefault(), ">", 100, 0).y) / 2}, 100, 0, BLACK);
        DrawTextEx(GetFontDefault(), "-", (Vector2){1785, 45 + 800 + 5 + (100 - MeasureTextEx(GetFontDefault(), "-", 100, 0).y) / 2}, 100, 0, BLACK);
        DrawTextEx(GetFontDefault(), "-", (Vector2){1745, 45 + 800 + 5 + (100 - MeasureTextEx(GetFontDefault(), "-", 100, 0).y) / 2}, 100, 0, BLACK);
        DrawTextEx(MyFont, "CONTINUE", (Vector2){1440, 800 + 45 + (100 - MeasureTextEx(MyFont, "CONTINUE", 50, 0).y) / 2}, 50, 0, BLACK);
    EndTextureMode();
}  

void UnloadChooseDataScene(void) {
    for (int i = 0; i < ChooseDataScenes.size(); i++) {
        for (int j = 0; j < ChooseDataScenes[i].size(); j++) {
            UnloadRenderTexture(ChooseDataScenes[i][j]);
        }
    }

    UnloadRenderTexture(DrawnText);
}