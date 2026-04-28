#include <iostream>
#include <vector>
#include <cstdint>
#include <string>
#include "VisualizeAVLTree.h"
#include "AVLTree.h"
#include "InsertAVLTreeScene.h"
#include "DrawObjects.h"
#include "raylib.h"
#include "raymath.h"

using namespace std;

bool Visualizing = false;
bool EndVisualizing = false;
int scenex = 0;
vector <VisualizedTree*> InsertVisualizedNodes;
int InsertStatePos = 0;

void InsertNodeAVLTreeScene(vector <VisualizedTree*> &InsertVisualizedNodes) {
    static float timer = 0.0f;
    static bool started = false;
    static float duration = 1.0f;
    static int CurrentNode = 0;

    static Vector2 startNodePos;
    static Vector2 endEdgePos;

    for (int i = 0; i < min(CurrentNode, (int)InsertVisualizedNodes.size()); i++) {
        VisualizedTree* node = InsertVisualizedNodes[i];

        DrawRing(node->node.targetPos, node->node.radius - node->node.thickness, node->node.radius, 0.0f, 360.0f, 100, node->node.color);
        DrawShorterLineStartEnd(node->edge.targetStart, node->edge.targetEnd, 50.0f, node->edge.thickness, node->edge.color);
        DrawTextEx(GetFontDefault(), to_string(node->data).c_str(), Vector2Subtract(node->node.targetPos, MeasureTextEx(GetFontDefault(), to_string(node->data).c_str(), 30, 5) / 2), 30, 5, BLACK);
    }

    VisualizedTree* node = InsertVisualizedNodes[CurrentNode];

    if (!started) {
        timer = 0.0f;
        started = true;

        startNodePos = InsertVisualizedNodes[CurrentNode]->node.pos;
        endEdgePos = InsertVisualizedNodes[CurrentNode]->edge.end;
    }

    timer += GetFrameTime();

    float Time = timer / duration;
    Time = Clamp(Time, 0.0f, 1.0f);

    node->node.pos = Vector2Lerp(startNodePos, node->node.targetPos, Time);
    node->edge.end = Vector2Lerp(endEdgePos, node->edge.targetEnd, Time);

    DrawRing(node->node.pos, node->node.radius - node->node.thickness, node->node.radius, 0.0f, 360.0f, 100, RED);
    DrawShorterLineStartEnd(node->edge.start, node->node.pos, 50.0f, node->edge.thickness, RED);
    DrawTextEx(GetFontDefault(), to_string(node->data).c_str(), Vector2Subtract(node->node.pos, MeasureTextEx(GetFontDefault(), to_string(node->data).c_str(), 30, 3) / 2), 30, 3, RED);

    if (timer >= duration) {
        node->node.pos = node->node.targetPos;
        node->edge.end = node->edge.targetEnd;

        CurrentNode++;
        started = false;

        if (CurrentNode >= InsertVisualizedNodes.size()) {
            Visualizing = false;
            EndVisualizing = true;
        }
    }
}

void DrawInsertAVLTreeScene(void) { 
    static vector <VisualizedTree*> version2, OldVersion;

    if (AVLTreeState.size() == 0) {
        return;
    }
    else {
        if (scenex == 0) {
            if (!Visualizing) {
                OldVersion.clear();
                InsertVisualizedNodes.clear();
                version2.clear();

                long long data = RotateState[scenex].first;

                if (AVLTreeState[scenex] == nullptr) cout << -1 << endl;

                FlattenTheTree(AVLTreeState[scenex], InsertVisualizedNodes, version2, data);

                Visualizing = true;
            }

            for (int i = 0; i < InsertVisualizedNodes.size(); i++) {
                VisualizedTree* node = InsertVisualizedNodes[i];
                node->node.pos = node->node.targetPos;

                DrawRing(node->node.targetPos, node->node.radius - node->node.thickness, node->node.radius, 0.0f, 360.0f, 100, node->node.color);
                DrawShorterLineStartEnd(node->edge.start, node->node.targetPos, 50.0f, node->edge.thickness, node->edge.color);
                DrawTextEx(GetFontDefault(), to_string(node->data).c_str(), Vector2Subtract(node->node.pos, MeasureTextEx(GetFontDefault(), to_string(node->data).c_str(), 30, 3) / 2), 30, 3, BLACK);
            }

            InsertNodeAVLTreeScene(version2);

            if (EndVisualizing) {
                scenex++;
                EndVisualizing = false;
            }   
        }
        else if (scenex < AVLTreeState.size()) {
            if (!Visualizing) {
                Visualizing = true;

                OldVersion.clear();
                version2.clear();
                InsertVisualizedNodes.clear();

                FlattenTheTree(AVLTreeState[scenex - 1], OldVersion, version2, -1);
                FlattenTheTree(AVLTreeState[scenex], InsertVisualizedNodes, version2, RotateState[scenex].first);
                
                for (int i = 0; i < version2.size(); i++) {
                    for (int j = 0; j < OldVersion.size(); j++) {
                        if (version2[i]->data == OldVersion[j]->data) {
                            version2[i]->node.pos = OldVersion[j]->node.pos;
                        }
                    }
                }
            }

            for (int i = 0; i < InsertVisualizedNodes.size(); i++) {
                VisualizedTree* node = InsertVisualizedNodes[i];
                node->node.pos = node->node.targetPos;

                DrawRing(node->node.targetPos, node->node.radius - node->node.thickness, node->node.radius, 0.0f, 360.0f, 100, node->node.color);
                DrawShorterLineStartEnd(node->edge.start, node->node.targetPos, 50.0f, node->edge.thickness, node->edge.color);
                DrawTextEx(GetFontDefault(), to_string(node->data).c_str(), Vector2Subtract(node->node.pos, MeasureTextEx(GetFontDefault(), to_string(node->data).c_str(), 30, 3) / 2), 30, 3, BLACK);
            }

            InsertNodeAVLTreeScene(version2);

            if (EndVisualizing) {
                scenex++;
                EndVisualizing = false;
            }
        }
        else if (scenex == AVLTreeState.size()) {
            AVLTreeScene.push_back(AVLTreeState.back());
            AVLTreeState.clear();
            scenex = 0;
        }
    }
}