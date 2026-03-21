// HeapController.cpp
#include "HeapController.hpp"

HeapController::HeapController() {
	saveState();
}
bool HeapController::hasSteps() const {
	return !steps.empty();
}
Heap& HeapController::getHeap() {
	return heap;
}
void HeapController::push(int x) {
	Heap temp = heap;
	int id = temp.getSize();
	temp.pushRaw(x);
	steps.push({ HeapStep::Insert, -1, x });
	while (id > 0) {
		int parent = (id - 1) / 2;
		steps.push({ HeapStep::Compare, parent, id });
		if (temp[parent] >= temp[id]) break;
		steps.push({ HeapStep::Swap, parent, id });
		temp.swapAt(parent, id);
		id = parent;
	}
	steps.push({ HeapStep::Done, -1, -1 });
}
bool HeapController::pop(int& x) {
	if (heap.getSize() == 0) return false;
	Heap temp = heap;
	x = temp[0]; // return top
	int last = temp.getSize() - 1;
	// swap root with last
	steps.push({ HeapStep::Swap, 0, last });
	temp.swapAt(0, last);
	// remove last
	steps.push({ HeapStep::Remove, last, -1 });
	temp.removeLast();
	// downHeap simulation
	int id = 0;
	while (true) {
		int left = 2 * id + 1;
		int right = 2 * id + 2;
		int largest = id;
		if (left < temp.getSize()) {
			steps.push({ HeapStep::Compare, id, left });
			if (temp[left] > temp[largest]) largest = left;
		}
		if (right < temp.getSize()) {
			steps.push({ HeapStep::Compare, largest, right });
			if (temp[right] > temp[largest]) largest = right;
		}
		if (largest == id) break;
		steps.push({ HeapStep::Swap, id, largest });
		temp.swapAt(id, largest);
		id = largest;
	}
	steps.push({ HeapStep::Done, -1, -1 });
	return true;
}
int HeapController::getHighlightA() const {
	return highlightA;
}
int HeapController::getHighlightB() const {
	return highlightB;
}
void HeapController::saveState() {
	std::vector<int> snapshot;
	for (int i = 0; i < heap.getSize(); i++) snapshot.push_back(heap[i]); 
	// remove future states if we branched
	if (historyIndex < history.size() - 1) history.resize(historyIndex + 1);
	history.push_back(snapshot);
	historyIndex++;
}
void HeapController::nextStep() {
	if (steps.empty()) return;
	highlightA = -1;
	highlightB = -1;
	HeapStep step = steps.front();
	steps.pop();
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
	case HeapStep::Done:
		highlightA = -1;
		highlightB = -1;
		break;
	case HeapStep::Remove:
		heap.removeLast();
		break;
	}
	saveState();
}
void HeapController::runAll() {
	while (!steps.empty()) nextStep();
}
void HeapController::undo() {
	if (historyIndex == 0) return;
	historyIndex--;
	heap.clear();
	for (int v : history[historyIndex]) heap.pushRaw(v);
}
void HeapController::redo() {
	if (historyIndex >= history.size() - 1) return;
	historyIndex++;
	heap.clear();
	for (int v : history[historyIndex]) heap.pushRaw(v);
}