#pragma once

struct Node {
    int data;
    Node* next;

    Node(int value);
};

class LinkedList {
private:
    Node* head;
    int size;

public:
    // Constructor - Destructor
    LinkedList();
    LinkedList(const LinkedList& other);
    LinkedList& operator=(const LinkedList& other);
    ~LinkedList();

    // Basic functions
    void pushFront(int value);
    void pushBack(int value);
    bool insertAt(int index, int value);

    bool popFront();
    bool popBack();
    bool removeAt(int index);

    bool update(int index, int value);

    int search(int value) const;

    bool empty() const;
    int getSize() const;

    void clear();

    int get(int index) const;

public:
    // Multistep helpers (for visualization)
    void pushBackRaw(int value); 
};