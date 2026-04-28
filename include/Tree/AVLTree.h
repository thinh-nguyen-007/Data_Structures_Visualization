#include <iostream>
#include <string>
#include <vector>
#include <cstdint>
#include "raylib.h"
#include "raymath.h"
#pragma once

using namespace std;

class AVLTree {
public: 
    struct node {
        long long data;
        int height;
        node* left;
        node* right;

        node(int _data = 0) {
            data = _data;
            left = right = nullptr;
            height = 1;
        }
    };

    node* tree = nullptr;

public: 
    void Initialize(vector <long long> &a);
    void Update(node* tree, long long data);
    void updateHeight(node* tree);
    void DrawAVLTree(void);
    void RecuresiveDraw(node* tree, Vector2 parpos, int depth, int spacing, int width);
    bool checkLL(node* tree, long long data);
    bool checkRR(node* tree, long long data);
    bool checkLR(node* tree, long long data);
    bool checkRL(node* tree, long long data);
    int getHeight(node* tree);
    int getBalance(node* tree);
    node* Insert(node* &tree, long long data);
    node* Delete(node* &tree, long long data);
    node* getMinNode(node* tree);
    node* Search(node* tree, long long data);
    node* rotateLeft(node* tree);
    node* rotateRight(node* tree);
    vector <long long> LevelOrder(void);
};

extern AVLTree Tree;