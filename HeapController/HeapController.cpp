// HeapController.cpp
#include "HeapController.hpp"
#include "algorithm"

HeapController::HeapController() {
	currentMessage = "Ready";
}
void HeapController::clear() {
	heap.clear();
	steps.clear();
	stepIndex = 0;
	lastStepType = HeapStep::Done;
	paused = true;
	highlightA = -1;
	highlightB = -1;
	currentMessage.clear();
}
void HeapController::push(int x) {
	if (hasSteps()) steps.resize(stepIndex);
	paused = false;
	Heap temp = heap;
	int id = temp.getSize();
	temp.pushRaw(x);
	steps.push_back({ HeapStep::Insert, -1, x, "Insert " + std::to_string(x) });
	while (id > 0) {
		int parent = (id - 1) / 2;
		steps.push_back({ HeapStep::Compare, parent, id, "Compare " + std::to_string(temp[parent]) + " and " + std::to_string(temp[id]) });
		if (temp[parent] >= temp[id]) break;
		steps.push_back({ HeapStep::Swap, parent, id, "Swap " + std::to_string(temp[parent]) + " and " + std::to_string(temp[id]) });
		temp.swapAt(parent, id);
		id = parent;
	}
	steps.push_back({ HeapStep::Done, -1, -1, "Insert " + std::to_string(x) + " completed" });
}
bool HeapController::pop(int& x) {
	if (heap.getSize() == 0) return false;
	if (hasSteps()) steps.resize(stepIndex);
	paused = false;
	Heap temp = heap;
	x = temp[0]; // return top
	int last = temp.getSize() - 1;
	// swap root with last
	steps.push_back({ HeapStep::Swap, 0, last, "Swap root " + std::to_string(temp[0]) + " with " + std::to_string(temp[last]) });
	temp.swapAt(0, last);
	// remove last
	steps.push_back({ HeapStep::Remove, last, -1, "Remove " + std::to_string(temp[last]) });
	temp.removeLast();
	// downHeap simulation
	int id = 0;
	while (true) {
		int left = 2 * id + 1;
		int right = 2 * id + 2;
		int largest = id;
		if (left < temp.getSize()) {
			steps.push_back({ HeapStep::Compare, id, left, "Compare " + std::to_string(temp[id]) + " and " + std::to_string(temp[left]) });
			if (temp[left] > temp[largest]) largest = left;
		}
		if (right < temp.getSize()) {
			steps.push_back({ HeapStep::Compare, largest, right, "Compare " + std::to_string(temp[largest]) + " and " + std::to_string(temp[right]) });
			if (temp[right] > temp[largest]) largest = right;
		}
		if (largest == id) break;
		steps.push_back({ HeapStep::Swap, id, largest, "Swap " + std::to_string(temp[id]) + " and " + std::to_string(temp[largest]) });
		temp.swapAt(id, largest);
		id = largest;
	}
	steps.push_back({ HeapStep::Done, -1, -1, "Remove completed" });
	return true;
}
void HeapController::nextStep() {
	if (stepIndex >= steps.size()) return;
	const HeapStep& step = steps[stepIndex];
	highlightA = -1;
	highlightB = -1;
	lastStepType = step.type;
	currentMessage = step.message;
	switch (step.type)
	{
	case HeapStep::Insert:
		heap.pushRaw(step.b);
		break;
	case HeapStep::Swap:
		heap.swapAt(step.a, step.b);
		break;
	case HeapStep::Compare:
		highlightA = step.a;
		highlightB = step.b;
		break;
	case HeapStep::Remove:
		heap.removeLast();
		break;
	case HeapStep::Done:
		break;
	}
	stepIndex++; 
}
void HeapController::runToEnd() {
	while (isBusy()) nextStep();
	paused = true;
}
void HeapController::resetToStart() {
	stepIndex = 0;
	heap.clear();
	highlightA = -1;
	highlightB = -1;
	paused = true;
}
void HeapController::undo() {
	if (stepIndex <= 0) return;
	stepIndex--;
	rebuildHeapUpTo(stepIndex);
}
void HeapController::redo() {
	nextStep();
}
HeapStep::Type HeapController::peekNextStepType() const {
	if (stepIndex >= steps.size()) return HeapStep::Done;
	return steps[stepIndex].type;
}
int HeapController::peekNextA() const {
	if (stepIndex >= steps.size()) return -1;
	return steps[stepIndex].a;
}
void HeapController::searchVisual(int x) {
	if (isBusy()) return;
	if (hasSteps()) steps.resize(stepIndex);
	paused = false;
	int idx = heap.search(x);
	if (idx != -1) {
		steps.push_back({ HeapStep::Compare, idx, idx, "Found " + std::to_string(x) + " at index " + std::to_string(idx) });
	}
	steps.push_back({ HeapStep::Done, -1, -1, (idx != -1 ? "Search completed" : "Value not found") });
}
bool HeapController::isBusy() const {
	return stepIndex < steps.size();
}
bool HeapController::isAtOperationEnd() const {
	if (stepIndex == 0) return true;
	return steps[stepIndex - 1].type == HeapStep::Done;
}
void HeapController::rebuildHeapUpTo(int k) {
	heap.clear();
	highlightA = -1;
	highlightB = -1;
	for (int i = 0; i < k; i++) {
		const HeapStep& step = steps[i];
		lastStepType = step.type;
		currentMessage = step.message;
		switch (step.type) {
		case HeapStep::Insert:
			heap.pushRaw(step.b);
			break;
		case HeapStep::Swap:
			heap.swapAt(step.a, step.b);
			break;
		case HeapStep::Remove:
			heap.removeLast();
			break;
		case HeapStep::Compare:
			highlightA = step.a;
			highlightB = step.b;
			break;
		case HeapStep::Done:
			break;
		}
	}
}
void HeapController::heapifySteps(Heap& temp, int id, int size) {
	while (true) {
		int left = 2 * id + 1;
		int right = 2 * id + 2;
		int largest = id;
		if (left < size) {
			steps.push_back({ HeapStep::Compare, id, left, "Compare " + std::to_string(temp[id]) + " and " + std::to_string(temp[left]) });
			if (temp[left] > temp[largest]) largest = left;
		}
		if (right < size) {
			steps.push_back({ HeapStep::Compare, largest, right, "Compare " + std::to_string(temp[largest]) + " and " + std::to_string(temp[right]) });
			if (temp[right] > temp[largest]) largest = right;
		}
		if (largest == id) break;
		steps.push_back({ HeapStep::Swap, id, largest, "Swap " + std::to_string(temp[id]) + " and " + std::to_string(temp[largest]) });
		temp.swapAt(id, largest);
		id = largest;
	}
}
void HeapController::heapifyVisual(int i) {
	if (isBusy()) return;
	if (hasSteps()) steps.resize(stepIndex);
	Heap temp = heap;
	heapifySteps(temp, i, temp.getSize());
	steps.push_back({ HeapStep::Done, -1, -1, "Heapify completed" });
}
void HeapController::buildMaxHeapVisual() {
	if (isBusy()) return;
	if (hasSteps()) steps.resize(stepIndex);
	paused = false;
	Heap temp = heap;
	int n = temp.getSize();
	for (int i = n / 2 - 1; i >= 0; i--) {
		heapifySteps(temp, i, n);
	}
	steps.push_back({ HeapStep::Done, -1, -1, "Build Max Heap completed" });
}
void HeapController::heapSortVisual() {
	if (isBusy()) return;
	if (hasSteps()) steps.resize(stepIndex);
	paused = false;
	Heap temp = heap;
	int n = temp.getSize();
	// Build max heap
	for (int i = n / 2 - 1; i >= 0; i--) {
		heapifySteps(temp, i, n);
	}
	// Extract elements
	for (int end = n - 1; end > 0; end--) {
		steps.push_back({ HeapStep::Swap, 0, end, "Move max " + std::to_string(temp[0]) + " to position " + std::to_string(end) });
		temp.swapAt(0, end);
		heapifySteps(temp, 0, end);
	}
	steps.push_back({ HeapStep::Done, -1, -1, "Heap Sort completed" });
}
// file consistence
bool HeapController::loadFromFile(const std::string& filename) {
	std::ifstream fin(filename);
	if (!fin.is_open()) return false;
	std::vector<int> input;
	int x;
	while (fin >> x) input.push_back(x);
	if (input.empty()) return false; // no data
	clear();
	for (int i : input) heap.push(i);
	return true;
}
bool HeapController::saveToFile(const std::string& filename) {
	std::ofstream fout(filename);
	if (!fout.is_open()) return false;
	const auto& data = heap.getData();
	for (int i : data) {
		fout << i << " ";
	}
	return true;
}