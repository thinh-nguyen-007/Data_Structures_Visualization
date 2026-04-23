#pragma once

#include "Graph.h"
#include <vector>

// We introduce a struct to keep the algorithm contract standard.
// Any algorithm we create (Brute Force, DP, 2-opt) will return this struct.
struct TSPResult {
    std::vector<int> path; // The order of vertex IDs visited
    int totalCost;         // The total weight of this path
};

// Interface for our first algorithm (stub for now)
TSPResult TSP_BruteForce(const Graph& graph);
