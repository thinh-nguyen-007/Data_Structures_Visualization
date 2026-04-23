// HeapController.hpp
#pragma once
#include "Heap.hpp"
#include <queue>
#include <vector>
#include <string>

struct HeapStep {
	enum Type { Insert, Compare, Swap, Remove, Done };
	Type type;
	int a, b;
	std::string message;
};

struct HeapState {
	std::vector<int> data;
	std::string message;
	int highlightA;
	int highlightB;
};

class HeapController {
private:
	Heap heap;
	// support animation
	std::vector<HeapStep> steps;
	size_t stepIndex = 0;
	HeapStep::Type lastStepType = HeapStep::Done;
	bool paused = false;
	// highlight node index
	int highlightA = -1;
	int highlightB = -1;
	// message
	std::string currentMessage;
	// helpers
	bool hasSteps() const { return stepIndex < steps.size(); }
	void heapifySteps(Heap& temp, int id, int size);
public:
	// constructor
	HeapController();
	// functions
	void push(int x);
	bool pop(int& x);
	void searchVisual(int x);
	void heapifyVisual(int i);
	void buildMaxHeapVisual();
	void heapSortVisual();
	// logic state: condition - pause - next step - undo/redo
	bool isBusy() const;
	bool isPaused() const { return paused; }
	void setPaused(bool t) { paused = t; }
	void togglePaused() { paused = !paused; }
	void nextStep();
	void runToEnd();
	void resetToStart();
	bool isAtOperationEnd() const;
	void undo();
	void redo();
	void rebuildHeapUpTo(int k);
	// get data
	Heap& getHeap() { return heap; }
	int getHighlightA() const { return highlightA; }
	int getHighlightB() const { return highlightB; }
	size_t getStepIndex() const { return stepIndex; }
	const HeapStep& getCurrentStep() const { return steps[stepIndex - 1]; }
	std::string getMessage() const { return currentMessage; }
	HeapStep::Type getLastStepType() const { return lastStepType; }
	HeapStep::Type peekNextStepType() const;
	int peekNextA() const;
};
