// HeapController.hpp
#pragma once
#include "Heap.hpp"
#include <queue>
#include <vector>
struct HeapStep {
	enum Type { Insert, Compare, Swap, Remove, Done };
	Type type;
	int a, b;
};

class HeapController {
private:
	Heap heap;
	// support animation
	std::queue<HeapStep> steps;
	std::vector< std::vector<int >> history;
	int historyIndex = 0;
	// highlight node index
	int highlightA = -1;
	int highlightB = -1;
public:
	HeapController();
	Heap& getHeap();
	void push(int x);
	bool pop(int& x);
	void nextStep();
	void runAll();
	bool hasSteps() const;
	int getHighlightA() const;
	int getHighlightB() const;
	void saveState();
	void undo();
	void redo();
};
