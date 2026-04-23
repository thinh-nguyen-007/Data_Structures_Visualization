#include <iostream>
#include <vector>
#include <cstdint>
#include <string>
#include "snapshots.h"
#include "VisualizeAVLTree.h"
#include "raylib.h"
#include "raymath.h"

using namespace std;

void LoadSnapshots(void) {
    AVLTreeScenesInit();
}

void UnloadSnapshots(void) {
    UnloadAVLTreeScenes();
}