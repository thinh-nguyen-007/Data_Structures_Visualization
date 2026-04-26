#include <iostream>
#include <vector>
#include <string>
#include <cstdint>
#include "Textures.h"
#include "raylib.h"
#include "raymath.h"

using namespace std;

Image img;
Texture2D TestBackground;
Texture2D Background;
Font MyFont;

void LoadTextures(void) {
    img = LoadImage("assets/Background/StartingSceneBackground_1.png");
    TestBackground = LoadTextureFromImage(img);

    img = LoadImage("assets/Background/Scene.jpg");
    ImageFlipHorizontal(&img);

    MyFont = LoadFontEx("assets/Font/ZenDots-Regular.ttf", 128, 0, 0);
    Background = LoadTextureFromImage(img);
}

void UnloadTextures(void) {
    UnloadImage(img);
    UnloadFont(MyFont);
    UnloadTexture(Background);
}