// Heap.cpp
#include "../include/Heap.hpp"

// constructor
// default
Heap::Heap() {
    cap = 8; // default capacity
    size = 0;
    root = new int[cap];
}
// with cap
Heap::Heap(int capacity) {
    cap = capacity;
    size = 0;
    root = new int[cap];
}
// copy from other
Heap::Heap(const Heap& other) {
    size = other.size;
    cap = other.cap;
    root = new int[cap];
    for (int i = 0; i < size && i < cap; i++) root[i] = other.root[i];
}
// assignment
Heap& Heap::operator=(const Heap& other) {
    if (this == &other) return *this;
    delete[] root;
    size = other.size;
    cap = other.cap;
    root = new int[cap];
    for (int i = 0; i < size && i < cap; i++) root[i] = other.root[i];
    return *this;
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
// swap value of 2 indice
void Heap::swapAt(int a, int b) {
    int tmp = root[a];
    root[a] = root[b];
    root[b] = tmp;
}
// upheap
void Heap::upHeap(int id) {
    while (id > 0) {
        int parent = (id - 1) / 2;
        if (root[parent] >= root[id]) break;
        swapAt(parent, id);
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
        swapAt(id, largest);
        id = largest;
    }
}
// return top
int Heap::top() const {
    if (size == 0) return -1;
    return root[0];
}
// insert element
void Heap::push(int x) {
    if (size >= cap) resize();
    root[size] = x;
    upHeap(size);
    size++;
}
// remove root
void Heap::pop() {
    if (size == 0) return;
    root[0] = root[size - 1];
    size--;
    if (size > 0) downHeap(0);
}
// remove root and return value
bool Heap::pop(int& x) {
    if (size == 0) return false; 
    x = root[0];
    root[0] = root[size - 1];
    size--;
    if (size > 0) downHeap(0);
    return true;
}
// search element
int Heap::search(int x) const {
    for (int i = 0; i < size; i++) if (root[i] == x) return i;
    return -1;
}
// check empty
bool Heap::empty() const {
    return size == 0;
}
// return size
int Heap::getSize() const {
    return size;
}
// return vector of element
std::vector<int> Heap::getData() const {
    return std::vector<int>(root, root + size);
}
// decrement size
void Heap::removeLast() {
    if (size > 0) size--;
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
void Heap::pushRaw(int x){
    if (size >= cap) resize();
    root[size] = x;
    size++;
}