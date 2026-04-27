#pragma once
#include "LinkedList.hpp"
#include <vector>
#include <string>
#include <fstream>

// ===== Step =====
struct LinkedListStep {
    enum Type {
        Insert,
        Traverse,
        Delete,
        Update,
        Found,
        NotFound,
        Done
    };

    Type type;
    int index;
    int value;
    std::string message;
};

// ===== State (for visualization) =====
struct LinkedListState {
    std::vector<int> data;
    std::string message;
    int highlightIndex;
};

// ===== Controller =====
class LinkedListController {
private:
    LinkedList list;

    // animation support
    std::vector<LinkedListStep> steps;
    size_t stepIndex = 0;

    LinkedListStep::Type lastStepType = LinkedListStep::Done;

    bool paused = false;

    // highlight
    int highlightIndex = -1;

    // message
    std::string currentMessage;

    // helper
    bool hasSteps() const { return stepIndex < steps.size(); }

    void rebuildListUpTo(int k);

public:
    // constructor
    LinkedListController();

    // ===== Core operations =====
    void pushBack(int value);
    void pushFront(int value);
    void insertAt(int index, int value);

    void removeAt(int index);
    void popFront();
    void popBack();

    void update(int index, int value);

    void searchVisual(int value);

    void deleteValue(int x);

    // ===== Control animation =====
    bool isBusy() const;
    bool isPaused() const { return paused; }

    void setPaused(bool t) { paused = t; }
    void togglePaused() { paused = !paused; }

    void nextStep();
    void runToEnd();
    void resetToStart();

    bool isAtOperationEnd() const;
    bool canInteract() const { return !isBusy() || (isPaused() && isAtOperationEnd()); }

    void undo();
    void redo();

    // ===== Get data =====
    LinkedList& getList() { return list; }

    int getHighlightIndex() const { return highlightIndex; }

    size_t getStepIndex() const { return stepIndex; }

    const LinkedListStep& getCurrentStep() const { return steps[stepIndex - 1]; }

    std::string getMessage() const { return currentMessage; }

    LinkedListStep::Type getLastStepType() const { return lastStepType; }

    LinkedListStep::Type peekNextStepType() const;

    int peekNextIndex() const;

    void saveToFile(const std::string& filename);
    void loadFromFile(const std::string& filename);
};