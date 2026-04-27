#pragma once

#include "core/Graph.h"
#include <string>
#include <vector>


// An event snapshot for visualization
struct VisualizationEvent {
  std::vector<int> currentPath;
  std::vector<bool> visited;
  int currentCost;
  int bestCost;
  std::vector<int> bestPath;
  int sourceCodeLine; // For code highlighting
  std::string description;
};

// We introduce a struct to keep the algorithm contract standard.
// Any algorithm we create (Brute Force, DP, 2-opt) will return this struct.
struct TSPResult {
  std::vector<int> path;                  // The order of vertex IDs visited
  int totalCost;                          // The total weight of this path
  std::vector<VisualizationEvent> events; // History of steps for visualization
};

// Interface for our first algorithm (stub for now)
TSPResult TSP_BruteForce(const Graph &graph);

// Local search with 2-opt edge swaps.
TSPResult TSP_LocalSearch2Opt(const Graph &graph);
