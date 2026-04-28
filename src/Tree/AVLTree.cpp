#include <iostream>
#include <vector>
#include <cstdint>
#include <string>
#include <queue>
#include "AVLTree.h"
#include "DrawObjects.h"
#include "VisualizeAVLTree.h"
#include "raylib.h"
#include "raymath.h"

using namespace std;

AVLTree Tree;

void AVLTree::Initialize(vector <long long> &a) {
    for (int i = 0; i < a.size(); i++) 
    {
        tree = Insert(tree, a[i]);

        RotateState.clear();
        AVLTreeState.clear();
    }
}

void AVLTree::Update(node* tree, long long data) {

}

void AVLTree::updateHeight(node* tree) {
    tree->height = max(getHeight(tree->left), getHeight(tree->right)) + 1;
}

int AVLTree::getHeight(node* tree) {
    return ((tree) ? tree->height : 0);
}

int AVLTree::getBalance(node* tree) {
    return (getHeight(tree->left) - getHeight(tree->right));
}   

AVLTree::node* AVLTree::Insert(node* &tree, long long data) {
    if (tree == nullptr) {

        tree = new node(data);

        RotateState.push_back(make_pair(data, 0));
        CreateAVLTreeScene();

        return tree;
    }

    // cout << tree->data << endl;

    if (data < tree->data) 
        tree->left = Insert(tree->left, data);
    else if (data > tree->data)
        tree->right = Insert(tree->right, data);
    else if (data == tree->data)
        return tree;

    updateHeight(tree);

    int balance = getBalance(tree);

    // LL
    if (balance > 1 && data < tree->left->data) {
        tree = rotateRight(tree);
        
        RotateState.push_back(make_pair(tree->data, 2));
        CreateAVLTreeScene();

        return tree;
    }

    // RR
    if (balance < -1 && data > tree->right->data) {
        tree = rotateLeft(tree);

        RotateState.push_back(make_pair(tree->data, 1));
        CreateAVLTreeScene();

        return tree;
    }

    // LR
    if (balance > 1 && data > tree->left->data) {
        tree->left = rotateLeft(tree->left);

        RotateState.push_back(make_pair(tree->left->data, 1));
        CreateAVLTreeScene();

        tree = rotateRight(tree);

        RotateState.push_back(make_pair(tree->data, 2));
        CreateAVLTreeScene();

        return tree;
    }

    // RL
    if (balance < -1 && data < tree->right->data) {
        long long temp = tree->right->data;

        tree->right = rotateRight(tree->right);

        RotateState.push_back(make_pair(tree->right->data, 2));
        CreateAVLTreeScene();

        temp = tree->data;

        tree = rotateLeft(tree);

        RotateState.push_back(make_pair(tree->data, 1));
        CreateAVLTreeScene();

        return tree;
    }

    return tree;
}

AVLTree::node* AVLTree::Delete(node* tree, long long data) {
    if (tree == nullptr) return tree;

    if (data < tree->data)
        tree->left = Delete(tree->left, data);
    else if (data > tree->data)
        tree->right = Delete(tree->right, data);
    else {
        if (!tree->left || !tree->right) {
            node* temp = tree->left ? tree->left : tree->right;

            long long tmp = tree->data;

            if (!temp) {
                temp = tree;
                tree = nullptr;
            } else {
                *tree = *temp;
            }
            delete temp;

            RotateState.push_back(make_pair(tmp, 3));
            CreateAVLTreeScene();
        } else {
            node* temp = getMinNode(tree->right);
            tree->data = temp->data;
            tree->right = Delete(tree->right, temp->data);
        }
    }

    if (!tree) return tree;

    updateHeight(tree);
    int balance = getBalance(tree);

    // LL
    if (balance > 1 && getBalance(tree->left) >= 0) {
        RotateState.push_back({tree->data, 2});
        tree = rotateRight(tree);

        CreateAVLTreeScene();

        return tree;
    }

    // LR
    if (balance > 1 && getBalance(tree->left) < 0) {
        RotateState.push_back({tree->left->data, 1});
        RotateState.push_back({tree->data, 2});
        
        tree->left = rotateLeft(tree->left);
        CreateAVLTreeScene();

        tree = rotateRight(tree);
        CreateAVLTreeScene();

        return tree;
    }

    // RR
    if (balance < -1 && getBalance(tree->right) <= 0) {
        RotateState.push_back({tree->data, 1});
        tree = rotateLeft(tree);

        CreateAVLTreeScene();

        return tree;
    }

    // RL
    if (balance < -1 && getBalance(tree->right) > 0) {
        RotateState.push_back({tree->right->data, 2});
        RotateState.push_back({tree->data, 1});

        tree->right = rotateRight(tree->right);
        CreateAVLTreeScene();

        tree = rotateLeft(tree);
        CreateAVLTreeScene();

        return tree;
    }

    return tree;
}

AVLTree::node* AVLTree::getMinNode(node* tree) {
    if (tree->left) 
        return getMinNode(tree->left);
    else return tree; 
}

AVLTree::node* AVLTree::Search(node* tree, long long data) {
    if (tree == nullptr || tree->data == data)
        return tree;

    if (data < tree->data)
        return Search(tree->left, data);
    else return Search(tree->right, data);
}

AVLTree::node* AVLTree::rotateLeft(node* tree) {
    node* x = tree->right;
    node* y = x->left;

    x->left = tree;
    tree->right = y;

    updateHeight(tree);
    updateHeight(x);

    return x;
}

AVLTree::node* AVLTree::rotateRight(node* tree) {
    node* x = tree->left;
    node* y = x->right;

    x->right = tree;
    tree->left = y;

    updateHeight(tree);
    updateHeight(x);

    return x;
}

vector <long long> AVLTree::LevelOrder(void) {
    vector <long long> result;
    if (tree == nullptr) {
        return result;
    }

    queue <node*> q;
    q.push(tree);

    while (!q.empty()) {
        node* temp = q.front();
        q.pop();

        result.push_back(temp->data);

        if (temp->left) q.push(temp->left);
        if (temp->right) q.push(temp->right);
    }

    return result;
}