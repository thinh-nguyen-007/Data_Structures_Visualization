#include <iostream>
#include <vector>
#include <string>
#include <cstdint>
#include "SnapShots.h"
#include "raylib.h"
#include "raymath.h"
#include "StartingScene.h"
#include "ChooseDataScene.h"

using namespace std;

void LoadSnapShots(void) {
    StartingSceneInit();
    ChooseDataSceneInit();
}

void UnloadSnapShots(void) {
    UnloadStartingScene();
    UnloadChooseDataScene();
}