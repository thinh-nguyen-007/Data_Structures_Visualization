#include "LinkedListCommand.hpp"

// ===== Constructor =====
LinkedListController::LinkedListController() {
    currentMessage = "Ready";
}

// ===== Push Back (visual) =====
void LinkedListController::pushBack(int value) {
    if (hasSteps()) steps.resize(stepIndex);
    paused = false;

    LinkedList temp = list;

    int idx = 0;
    Node* cur = temp.getHead();

    // traverse
    while (cur) {
        steps.push_back({ LinkedListStep::Traverse, idx, cur->data,
            "Traverse node " + std::to_string(cur->data) });
        cur = cur->next;
        idx++;
    }

    // insert
    steps.push_back({ LinkedListStep::Insert, idx, value,
        "Insert " + std::to_string(value) + " at position " + std::to_string(idx) });

    steps.push_back({ LinkedListStep::Done, -1, -1, "Insert completed" });
}

// ===== Pop Front =====
void LinkedListController::popFront() {
    if (list.empty()) return;

    if (hasSteps()) steps.resize(stepIndex);
    paused = false;

    steps.push_back({ LinkedListStep::Delete, 0, list.get(0),
        "Remove head " + std::to_string(list.get(0)) });

    steps.push_back({ LinkedListStep::Done, -1, -1, "Remove completed" });
}

// ===== Remove At =====
void LinkedListController::removeAt(int index) {
    if (index < 0 || index >= list.getSize()) return;

    if (hasSteps()) steps.resize(stepIndex);
    paused = false;

    for (int i = 0; i < index; i++) {
        steps.push_back({ LinkedListStep::Traverse, i, list.get(i),
            "Traverse node " + std::to_string(list.get(i)) });
    }

    steps.push_back({ LinkedListStep::Delete, index, list.get(index),
        "Delete node " + std::to_string(list.get(index)) });

    steps.push_back({ LinkedListStep::Done, -1, -1, "Delete completed" });
}

// ===== Update =====
void LinkedListController::update(int index, int value) {
    if (index < 0 || index >= list.getSize()) return;

    if (hasSteps()) steps.resize(stepIndex);
    paused = false;

    for (int i = 0; i <= index; i++) {
        steps.push_back({ LinkedListStep::Traverse, i, list.get(i),
            "Traverse node " + std::to_string(list.get(i)) });
    }

    steps.push_back({ LinkedListStep::Update, index, value,
        "Update node at " + std::to_string(index) + " to " + std::to_string(value) });

    steps.push_back({ LinkedListStep::Done, -1, -1, "Update completed" });
}

// ===== Search =====
void LinkedListController::searchVisual(int value) {
    if (isBusy()) return;
    if (hasSteps()) steps.resize(stepIndex);
    paused = false;

    int n = list.getSize();
    for (int i = 0; i < n; i++) {
        steps.push_back({ LinkedListStep::Traverse, i, list.get(i),
            "Check node " + std::to_string(list.get(i)) });

        if (list.get(i) == value) {
            steps.push_back({ LinkedListStep::Found, i, value,
                "Found " + std::to_string(value) + " at index " + std::to_string(i) });
            steps.push_back({ LinkedListStep::Done, -1, -1, "Search completed" });
            return;
        }
    }

    steps.push_back({ LinkedListStep::NotFound, -1, value,
        "Value not found" });

    steps.push_back({ LinkedListStep::Done, -1, -1, "Search completed" });
}

// ===== Next Step =====
void LinkedListController::nextStep() {
    if (stepIndex >= steps.size()) return;

    const LinkedListStep& step = steps[stepIndex];

    highlightIndex = -1;
    lastStepType = step.type;
    currentMessage = step.message;

    switch (step.type)
    {
    case LinkedListStep::Insert:
        list.pushBackRaw(step.value);
        break;

    case LinkedListStep::Delete:
        list.removeAt(step.index);
        break;

    case LinkedListStep::Update:
        list.update(step.index, step.value);
        break;

    case LinkedListStep::Traverse:
        highlightIndex = step.index;
        break;

    case LinkedListStep::Found:
        highlightIndex = step.index;
        break;

    case LinkedListStep::NotFound:
        break;

    case LinkedListStep::Done:
        break;
    }

    stepIndex++;
}

// ===== Run all =====
void LinkedListController::runToEnd() {
    while (isBusy()) nextStep();
    paused = true;
}

// ===== Reset =====
void LinkedListController::resetToStart() {
    stepIndex = 0;
    list.clear();
    highlightIndex = -1;
    paused = true;
}

// ===== Undo =====
void LinkedListController::undo() {
    if (stepIndex <= 0) return;
    stepIndex--;
    rebuildListUpTo(stepIndex);
}

// ===== Redo =====
void LinkedListController::redo() {
    nextStep();
}

// ===== Peek =====
LinkedListStep::Type LinkedListController::peekNextStepType() const {
    if (stepIndex >= steps.size()) return LinkedListStep::Done;
    return steps[stepIndex].type;
}

int LinkedListController::peekNextIndex() const {
    if (stepIndex >= steps.size()) return -1;
    return steps[stepIndex].index;
}

// ===== State =====
bool LinkedListController::isBusy() const {
    return stepIndex < steps.size();
}

bool LinkedListController::isAtOperationEnd() const {
    if (stepIndex == 0) return true;
    return steps[stepIndex - 1].type == LinkedListStep::Done;
}

// ===== Rebuild =====
void LinkedListController::rebuildListUpTo(int k) {
    list.clear();
    highlightIndex = -1;

    for (int i = 0; i < k; i++) {
        const LinkedListStep& step = steps[i];

        lastStepType = step.type;
        currentMessage = step.message;

        switch (step.type) {
        case LinkedListStep::Insert:
            list.pushBackRaw(step.value);
            break;

        case LinkedListStep::Delete:
            list.removeAt(step.index);
            break;

        case LinkedListStep::Update:
            list.update(step.index, step.value);
            break;

        case LinkedListStep::Traverse:
        case LinkedListStep::Found:
            highlightIndex = step.index;
            break;

        default:
            break;
        }
    }
}

void LinkedListController::saveToFile(const std::string& filename) {
    std::ofstream out(filename);

    if (!out) {
        currentMessage = "Failed to save file!";
        return;
    }

    for (int i = 0; i < list.getSize(); i++) {
        out << list.get(i) << " ";
    }

    out.close();

    currentMessage = "Saved to " + filename;
}

void LinkedListController::saveToFile() {
    saveToFile("data.txt");
}

void LinkedListController::loadFromFile(const std::string& filename) {
    std::ifstream in(filename);

    if (!in) {
        currentMessage = "Cannot open file";
        return;
    }

    list.clear();
    steps.clear();
    highlightIndex = -1;

    int x;
    while (in >> x) {
        list.pushBack(x);
    }

    in.close();

    currentMessage = "Loaded from " + filename;
}

void LinkedListController::loadFromFile() {
    loadFromFile("data.txt");
}

void LinkedListController::deleteValue(int x) {
    steps.clear();

    LinkedList& list = getList();

    Node* cur = list.getHead();
    int idx = 0;

    while (cur) {
        steps.push_back({ LinkedListStep::Traverse, idx });

        if (cur->data == x) {
            steps.push_back({ LinkedListStep::Delete, idx });
            list.removeAt(idx);
            currentMessage = "Deleted " + std::to_string(x);
            return;
        }

        cur = cur->next;
        idx++;
    }

    currentMessage = "Value not found";
}