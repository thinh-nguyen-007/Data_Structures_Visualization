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
	// highlight node index
	int highlightA = -1;
	int highlightB = -1;
	// message
	std::string currentMessage;
	// helpers
	bool hasSteps() const;
public:
	HeapController();
	Heap& getHeap();
	void push(int x);
	bool pop(int& x);
	void searchVisual(int x);
	// logic state - step - undo/redo
	void nextStep();
	void runAll();
	int getHighlightA() const;
	int getHighlightB() const;
	size_t getStepIndex() const;
	const HeapStep& getCurrentStep() const;
	void undo();
	void redo();
	std::string getMessage() const;
	HeapStep::Type getLastStepType() const;
	HeapStep::Type peekNextStepType() const;
	int peekNextA() const;
	bool isBusy() const;
	void rebuildHeapUpTo(int k);
};
