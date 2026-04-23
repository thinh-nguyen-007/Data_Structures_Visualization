#include <iostream>
#include <vector>
#include <cstdint>
#include <string>
#include "VisualizeAVLTree.h"
#include "raylib.h"
#include "raymath.h"

using namespace std;

vector < vector <RenderTexture2D> > AVLTreeScenes;

void AVLTreeScenesInit(void) {
    vector <RenderTexture2D> temp;

    temp.emplace_back(LoadRenderTexture(GetScreenWidth(), GetScreenHeight()));

    AVLTreeScenes.emplace_back(temp);

    BeginTextureMode(AVLTreeScenes[0][0]);
        ClearBackground(RAYWHITE);

        Tree.DrawAVLTree();
    EndTextureMode();
}

void UnloadAVLTreeScenes(void) {
    for (int i = 0; i < AVLTreeScenes.size(); i++) {
        for (int j = 0; j < AVLTreeScenes[i].size(); j++) 
            UnloadRenderTexture(AVLTreeScenes[i][j]);
    }
}