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
public: // basic interfaces
    Heap();
    Heap(int capacity);
    Heap(const Heap& other);
    Heap& operator=(const Heap& other);
    ~Heap();
    void swapAt(int a, int b);
    void push(int x);
    bool pop(int& x); 
    void pop();
    int top() const;
    bool search(int x) const;
    bool empty() const;
    int getSize() const;
    void removeLast();
    void clear();
    int operator[](int id) const;
public: // multistep helpers
    void pushRaw(int x);
};