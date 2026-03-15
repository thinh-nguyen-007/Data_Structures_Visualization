// Heap.hpp
#pragma once

class Heap {
private:
    int* root;
    int size;
    int cap;
    void upHeap(int id);
    void downHeap(int id);
    void resize();
public:
    Heap();
    Heap(int capacity);
    ~Heap();
    void push(int x);
    bool pop(int& x); 
    bool search(int x) const;
    bool empty() const;
    int getSize() const;
    void clear();
    int operator[](int id) const;
};