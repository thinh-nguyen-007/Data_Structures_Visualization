#include "../include/LinkedList.hpp"

// ===== Node constructor =====
Node::Node(int value) {
    data = value;
    next = nullptr;
}

// ===== Constructor =====
LinkedList::LinkedList() {
    head = nullptr;
    size = 0;
}

// ===== Copy constructor =====
LinkedList::LinkedList(const LinkedList& other) {
    head = nullptr;
    size = 0;

    Node* cur = other.head;
    while (cur) {
        pushBack(cur->data);
        cur = cur->next;
    }
}

// ===== Assignment operator =====
LinkedList& LinkedList::operator=(const LinkedList& other) {
    if (this == &other) return *this;

    clear();

    Node* cur = other.head;
    while (cur) {
        pushBack(cur->data);
        cur = cur->next;
    }

    return *this;
}

// ===== Destructor =====
LinkedList::~LinkedList() {
    clear();
}

// ===== Push Front =====
void LinkedList::pushFront(int value) {
    Node* newNode = new Node(value);
    newNode->next = head;
    head = newNode;
    size++;
}

// ===== Push Back =====
void LinkedList::pushBack(int value) {
    Node* newNode = new Node(value);

    if (!head) {
        head = newNode;
    } else {
        Node* cur = head;
        while (cur->next) cur = cur->next;
        cur->next = newNode;
    }

    size++;
}

// ===== Insert At =====
bool LinkedList::insertAt(int index, int value) {
    if (index < 0 || index > size) return false;

    if (index == 0) {
        pushFront(value);
        return true;
    }

    Node* cur = head;
    for (int i = 0; i < index - 1; i++) cur = cur->next;

    Node* newNode = new Node(value);
    newNode->next = cur->next;
    cur->next = newNode;

    size++;
    return true;
}

// ===== Pop Front =====
bool LinkedList::popFront() {
    if (!head) return false;

    Node* tmp = head;
    head = head->next;
    delete tmp;

    size--;
    return true;
}

// ===== Pop Back =====
bool LinkedList::popBack() {
    if (!head) return false;

    if (!head->next) {
        delete head;
        head = nullptr;
    } else {
        Node* cur = head;
        while (cur->next->next) cur = cur->next;

        delete cur->next;
        cur->next = nullptr;
    }

    size--;
    return true;
}

// ===== Remove At =====
bool LinkedList::removeAt(int index) {
    if (index < 0 || index >= size) return false;

    if (index == 0) return popFront();

    Node* cur = head;
    for (int i = 0; i < index - 1; i++) cur = cur->next;

    Node* tmp = cur->next;
    cur->next = tmp->next;
    delete tmp;

    size--;
    return true;
}

// ===== Update =====
bool LinkedList::update(int index, int value) {
    if (index < 0 || index >= size) return false;

    Node* cur = head;
    for (int i = 0; i < index; i++) cur = cur->next;

    cur->data = value;
    return true;
}

// ===== Search =====
int LinkedList::search(int value) const {
    Node* cur = head;
    int index = 0;

    while (cur) {
        if (cur->data == value) return index;
        cur = cur->next;
        index++;
    }

    return -1;
}

// ===== Empty =====
bool LinkedList::empty() const {
    return size == 0;
}

// ===== Get Size =====
int LinkedList::getSize() const {
    return size;
}

// ===== Clear =====
void LinkedList::clear() {
    while (head) {
        Node* tmp = head;
        head = head->next;
        delete tmp;
    }
    size = 0;
}

// ===== Get value at index =====
int LinkedList::get(int index) const {
    if (index < 0 || index >= size) return -1;

    Node* cur = head;
    for (int i = 0; i < index; i++) cur = cur->next;

    return cur->data;
}

// ===== Raw push (for visualization) =====
void LinkedList::pushBackRaw(int value) {
    Node* newNode = new Node(value);

    if (!head) {
        head = newNode;
    } else {
        Node* cur = head;
        while (cur->next) cur = cur->next;
        cur->next = newNode;
    }

    size++;
}