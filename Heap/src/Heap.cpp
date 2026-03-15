// Heap.cpp
#include "../include/Heap.hpp"
#include <algorithm>

// constructor
Heap::Heap() {
    cap = 8; // default capacity
    size = 0;
    root = new int[cap];
}
Heap::Heap(int capacity) {
    cap = capacity;
    size = 0;
    root = new int[cap];
}
// destructor
Heap::~Heap() {
    delete[] root;
}
// resize array when full
void Heap::resize() {
    cap *= 2;
    int* tmp = new int[cap];
    for (int i = 0; i < size; i++) tmp[i] = root[i];
    delete[] root;
    root = tmp;
}
// upheap
void Heap::upHeap(int id) {
    while (id > 0) {
        int parent = (id - 1) / 2;
        if (root[parent] >= root[id]) break;
        std::swap(root[parent], root[id]);
        id = parent;
    }
}
// downheap
void Heap::downHeap(int id) {
    while (true) {
        int left = 2 * id + 1;
        int right = 2 * id + 2;
        int largest = id;
        if (left < size && root[left] > root[largest]) largest = left;
        if (right < size && root[right] > root[largest]) largest = right;
        if (largest == id) break;
        std::swap(root[id], root[largest]);
        id = largest;
    }
}
// insert element
void Heap::push(int x) {
    if (size >= cap) resize();
    root[size] = x;
    upHeap(size);
    size++;
}
// remove root
bool Heap::pop(int& x) {
    if (size == 0) return false; 
    x = root[0];
    root[0] = root[size - 1];
    size--;
    if (size > 0) downHeap(0);
    return true;
}
// search element
bool Heap::search(int x) const {
    for (int i = 0; i < size; i++) if (root[i] == x) return true;
    return false;
}
// check empty
bool Heap::empty() const {
    return size == 0;
}
// return size
int Heap::getSize() const {
    return size;
}
// clear heap
void Heap::clear() {
    size = 0;
}
// index operator
int Heap::operator[](int id) const {
    if (id < 0 || id >= size) return -1;
    return root[id];
}