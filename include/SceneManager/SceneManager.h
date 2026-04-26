#include <iostream>
#include <vector>
#include <string>
#include <cstdint>
#include "raylib.h"
#include "raymath.h"
#include "MyColors.h"
#include "Textures.h"
#pragma once

using namespace std;

class SceneManager {
private:
    Camera2D camera = {0};
    float ScreenWidth, ScreenHeight;
    /*
    SceneNumber = 0: Starting Screen
    SceneNumber = 1: Choose Data Structures
    SceneNumber = 2: Settings

    SceneNumber = 3: Heap
    SceneNumber = 4: Tree
    SceneNumber = 4: List
    SceneNumber = 6: Graph
    */
    int SceneNumber; 

public:
    SceneManager() {
        ScreenWidth = GetScreenWidth();
        ScreenHeight = GetScreenHeight();

        camera.target = (Vector2){0, 0};
        camera.offset = (Vector2){0, 0};
        camera.zoom = 1.0f;

        SceneNumber = 0;
    }

    void StartingScene();
    void ChooseDataScene();
    void SettingScene();
    void ScreenDeployment(void);
    void UpdateSceneNumber(int number) {
        SceneNumber = number;
    }
    int GetSceneNumber(void) const {
        return SceneNumber;
    }
};