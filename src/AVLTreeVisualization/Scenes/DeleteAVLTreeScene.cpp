#include <iostream>
#include <vector>
#include <cstdint>
#include <string>
#include "VisualizeAVLTree.h"
#include "DeleteAVLTreeScene.h"
#include "AVLTree.h"
#include "DrawObjects.h"
#include "raylib.h"
#include "raymath.h"

using namespace std;

namespace {
    bool Visualizing = false;
    bool EndVisualizing = false;
    bool DeleteYet = false;
    bool EndVisualizing1 = false;
    int scenex = 1;
    vector <VisualizedTree*> DeleteVisualizedNodes;
}

void DeleteNodes(vector <VisualizedTree*> &DeleteVisualizedNodes) {
    static float timer = 0.0f;
    static bool started = false;
    static float duration = 2.0f;
    static int CurrentNode = DeleteVisualizedNodes.size();   

    if (!started) {
        timer = 0.0f;
        started = true;
    }

    timer += GetFrameTime();

    float Time = timer / duration;
    Time = Clamp(Time, 0.0f, 1.0f);

    for (int i = 0; i < DeleteVisualizedNodes.size(); i++) {
        VisualizedTree* node = DeleteVisualizedNodes[i];

        DrawRing(node->node.targetPos, node->node.radius - node->node.thickness, node->node.radius, 0.0f, 360.0f, 100, Fade(RED, 1.0f - Time));
        DrawShorterLineStartEnd(node->edge.start, node->node.targetPos, 50.0f, 5.0f, Fade(RED, 1.0f - Time));
        DrawTextEx(GetFontDefault(), to_string(node->data).c_str(), Vector2Subtract(node->node.targetPos, MeasureTextEx(GetFontDefault(), to_string(node->data).c_str(), 30, 5) / 2), 30, 5, Fade(RED, 1.0f - Time));
    }

    if (timer >= duration) {
        CurrentNode++;
        started = false;

        if (CurrentNode >= DeleteVisualizedNodes.size()) {
            EndVisualizing1 = true;
            CurrentNode = 0;
        }
    }
}

void DeleteNodeAVLTreeScene(vector <VisualizedTree*> &DeleteVisualizedNodes) {
    static float timer = 0.0f;
    static bool started = false;
    static float duration = 1.0f;
    static int CurrentNode = 0;

    static Vector2 startNodePos;
    static Vector2 endEdgePos;

    for (int i = 0; i < min(CurrentNode, (int)DeleteVisualizedNodes.size()); i++) {
        VisualizedTree* node = DeleteVisualizedNodes[i];

        DrawRing(node->node.targetPos, node->node.radius - node->node.thickness, node->node.radius, 0.0f, 360.0f, 100, node->node.color);
        DrawShorterLineStartEnd(node->edge.targetStart, node->edge.targetEnd, 50.0f, node->edge.thickness, node->edge.color);
        DrawTextEx(GetFontDefault(), to_string(node->data).c_str(), Vector2Subtract(node->node.targetPos, MeasureTextEx(GetFontDefault(), to_string(node->data).c_str(), 30, 5) / 2), 30, 5, BLACK);
    }

    VisualizedTree* node = DeleteVisualizedNodes[CurrentNode];

    if (!started) {
        timer = 0.0f;
        started = true;

        startNodePos = DeleteVisualizedNodes[CurrentNode]->node.pos;
        endEdgePos = DeleteVisualizedNodes[CurrentNode]->edge.end;
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

        if (CurrentNode >= DeleteVisualizedNodes.size()) {
            Visualizing = false;
            EndVisualizing = true;
            CurrentNode = 0;
        }
    }
}

void DrawDeleteAVLTreeScene(void) {
    static vector <VisualizedTree*> version2, OldVersion;
    static VisualizedTree* DeleteNode;
    static vector <VisualizedTree*> NeedToDelete;

    if (AVLTreeState.size() == 1) {
        return;
    }
    else {
        if (scenex < AVLTreeState.size()) {
            if (!Visualizing) {
                Visualizing = true;
                long long data = RotateState[scenex].first;

                OldVersion.clear();
                version2.clear();
                DeleteVisualizedNodes.clear();
                NeedToDelete.clear();

                FlattenTheTree(AVLTreeState[scenex - 1], OldVersion, version2, -1);
                FlattenTheTree(AVLTreeState[scenex], DeleteVisualizedNodes, version2, -1);
                
                vector <VisualizedTree*> temp;

                for (int j = 0; j < OldVersion.size(); j++) {

                    bool CheckAvailable = false;

                    for (int i = 0; i < DeleteVisualizedNodes.size(); i++) {
                        if (DeleteVisualizedNodes[i]->data == OldVersion[j]->data) {
                            CheckAvailable = true;

                            if (DeleteVisualizedNodes[i]->node.targetPos != OldVersion[j]->node.targetPos) {
                                version2.push_back(DeleteVisualizedNodes[i]);
                                version2.back()->node.pos = OldVersion[j]->node.targetPos;
                            }
                            else {
                                temp.push_back(DeleteVisualizedNodes[i]);
                            }
                        }
                    }

                    if (!CheckAvailable) {
                        NeedToDelete.push_back(OldVersion[j]);
                    }
                }

                for (int i = 0; i < version2.size(); i++) {
                    cout << version2[i]->data << " ";
                }

                cout << endl;

                DeleteVisualizedNodes.swap(temp);
            }

            for (int i = 0; i < DeleteVisualizedNodes.size(); i++) {
                VisualizedTree* node = DeleteVisualizedNodes[i];
                node->node.pos = node->node.targetPos;

                DrawRing(node->node.targetPos, node->node.radius - node->node.thickness, node->node.radius, 0.0f, 360.0f, 100, node->node.color);
                DrawShorterLineStartEnd(node->edge.start, node->node.targetPos, 50.0f, node->edge.thickness, node->edge.color);
                DrawTextEx(GetFontDefault(), to_string(node->data).c_str(), Vector2Subtract(node->node.pos, MeasureTextEx(GetFontDefault(), to_string(node->data).c_str(), 30, 3) / 2), 30, 3, BLACK);
            }

            if (!EndVisualizing1) {
                cout << scenex << " ____ " << NeedToDelete.size() << endl;

                for (int i = 0; i < NeedToDelete.size(); i++) {
                    cout << NeedToDelete[i]->data << endl;
                    cout << NeedToDelete[i]->node.pos.x << " " << NeedToDelete[i]->node.pos.y << endl;
                    cout << NeedToDelete[i]->node.targetPos.x << " " << NeedToDelete[i]->node.targetPos.y << endl;
                }

                DeleteNodes(NeedToDelete);
            }
            else {
                if (version2.size()) {
                    DeleteNodeAVLTreeScene(version2);
                }
                else {
                    EndVisualizing = true;
                }
            }

            if (EndVisualizing) {
                scenex++;
                EndVisualizing = false;
                EndVisualizing1 = false;
            }   
        }
        /*else if (scenex < AVLTreeState.size()) {
            if (!Visualizing) {
                Visualizing = true;

                OldVersion.clear();
                version2.clear();
                DeleteVisualizedNodes.clear();

                FlattenTheTree(AVLTreeState[scenex - 1], OldVersion, version2, -1);
                FlattenTheTree(AVLTreeState[scenex], DeleteVisualizedNodes, version2, RotateState[scenex].first);
                
                for (int i = 0; i < version2.size(); i++) {
                    for (int j = 0; j < OldVersion.size(); j++) {
                        if (version2[i]->data == OldVersion[j]->data) {
                            version2[i]->node.pos = OldVersion[j]->node.pos;
                        }
                    }
                }
            }

            for (int i = 0; i < DeleteVisualizedNodes.size(); i++) {
                VisualizedTree* node = DeleteVisualizedNodes[i];
                node->node.pos = node->node.targetPos;

                DrawRing(node->node.targetPos, node->node.radius - node->node.thickness, node->node.radius, 0.0f, 360.0f, 100, node->node.color);
                DrawShorterLineStartEnd(node->edge.start, node->node.targetPos, 50.0f, node->edge.thickness, node->edge.color);
                DrawTextEx(GetFontDefault(), to_string(node->data).c_str(), Vector2Subtract(node->node.pos, MeasureTextEx(GetFontDefault(), to_string(node->data).c_str(), 30, 3) / 2), 30, 3, BLACK);
            }

            DeleteNodeAVLTreeScene(version2);

            if (EndVisualizing) {
                scenex++;
                EndVisualizing = false;
            }
        }*/
        else if (scenex >= AVLTreeState.size()) {
            AVLTreeScene.push_back(AVLTreeState.back());
            AVLTreeState.clear();
            RotateState.clear();
            scenex = 0;
        }
    }
}