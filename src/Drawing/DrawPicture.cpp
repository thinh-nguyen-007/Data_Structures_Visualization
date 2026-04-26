#include <iostream>
#include <vector>
#include <string>
#include <cstdint>
#include "DrawText.h"
#include "DrawPicture.h"
#include "raymath.h"
#include "raylib.h"
#include "Textures.h"

using namespace std;

void DrawPicture(Texture2D texture, Vector2 position, float rotation, float scale, Color tint) {
    DrawTextureEx(texture, position, rotation, scale, tint);
}