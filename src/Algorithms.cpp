#include "Algorithms.h"
#include "Graph.h"
#include <algorithm>
#include <limits> // Required for std::numeric_limits
#include <random>
#include <string>

namespace {

std::vector<int> BuildInitialNearestNeighborTour(const Graph &graph);

int CalculatePathCost(const Graph &graph, const std::vector<int> &path) {
  if (path.size() < 2) {
    return std::numeric_limits<int>::max();
  }

  int totalCost = 0;
  for (size_t i = 0; i + 1 < path.size(); ++i) {
    int weight = graph.GetEdgeWeight(path[i], path[i + 1]);
    if (weight <= 0) {
      return std::numeric_limits<int>::max();
    }
    totalCost += weight;
  }
  return totalCost;
}

std::vector<int> BuildInitialRandomTour(const Graph &graph) {
  int n = graph.GetVertexCount();
  if (n == 0) {
    return {};
  }

  // Build a random valid tour incrementally; this is much more reliable than
  // testing random full permutations on sparse directed graphs.
  static std::mt19937 rng(std::random_device{}());
  const int maxAttempts = std::max(300, n * 80);

  for (int attempt = 0; attempt < maxAttempts; ++attempt) {
    std::vector<int> tour;
    std::vector<bool> visited(n, false);
    int current = 0;

    tour.push_back(0);
    visited[0] = true;
    bool failed = false;

    for (int step = 1; step < n; ++step) {
      std::vector<int> candidates;
      for (int next = 1; next < n; ++next) {
        if (!visited[next] && graph.GetEdgeWeight(current, next) > 0) {
          candidates.push_back(next);
        }
      }

      if (candidates.empty()) {
        failed = true;
        break;
      }

      std::shuffle(candidates.begin(), candidates.end(), rng);

      int chosen = candidates.front();
      visited[chosen] = true;
      tour.push_back(chosen);
      current = chosen;
    }

    if (failed) {
      continue;
    }

    if (graph.GetEdgeWeight(current, 0) <= 0) {
      continue;
    }

    tour.push_back(0);
    int cost = CalculatePathCost(graph, tour);
    if (cost != std::numeric_limits<int>::max()) {
      return tour;
    }
  }

  // Fallback: try nearest-neighbor so 2-opt can still run on many inputs.
  std::vector<int> nearestTour = BuildInitialNearestNeighborTour(graph);
  if (!nearestTour.empty()) {
    return nearestTour;
  }

  return {};
}

std::vector<int> BuildInitialNearestNeighborTour(const Graph &graph) {
  int n = graph.GetVertexCount();
  if (n == 0) {
    return {};
  }

  std::vector<int> tour;
  std::vector<bool> visited(n, false);
  int current = 0;

  tour.push_back(current);
  visited[current] = true;

  for (int step = 1; step < n; ++step) {
    int bestNext = -1;
    int bestWeight = std::numeric_limits<int>::max();

    for (int candidate = 0; candidate < n; ++candidate) {
      if (visited[candidate]) {
        continue;
      }

      int weight = graph.GetEdgeWeight(current, candidate);
      if (weight > 0 && weight < bestWeight) {
        bestWeight = weight;
        bestNext = candidate;
      }
    }

    if (bestNext == -1) {
      return {};
    }

    tour.push_back(bestNext);
    visited[bestNext] = true;
    current = bestNext;
  }

  if (graph.GetEdgeWeight(current, 0) <= 0) {
    return {};
  }

  tour.push_back(0);
  return tour;
}

std::vector<bool> BuildVisitedMask(int vertexCount, const std::vector<int> &path) {
  std::vector<bool> visited(vertexCount, false);
  for (int node : path) {
    if (node >= 0 && node < vertexCount) {
      visited[node] = true;
    }
  }
  return visited;
}

void PushEvent(std::vector<VisualizationEvent> &events, const Graph &graph,
               const std::vector<int> &currentPath, int currentCost,
               int bestCost, const std::vector<int> &bestPath,
               int sourceCodeLine, const std::string &description) {
  events.push_back({currentPath,
                    BuildVisitedMask(graph.GetVertexCount(), currentPath),
                    currentCost,
                    bestCost,
                    bestPath,
                    sourceCodeLine,
                    description});
}

} // namespace

// Recursive helper function for Backtracking
void TSP_Backtrack_Helper(const Graph &graph, int currPos, int numVisited,
                          int currCost, std::vector<int> &currPath,
                          std::vector<bool> &visited, int &minCost,
                          std::vector<int> &bestPath,
                          std::vector<VisualizationEvent> &events) {

  int numVertices = graph.GetVertexCount();
  
  // Record event for entering node
  events.push_back({currPath, visited, currCost, minCost, bestPath, 1, "Visiting node " + std::to_string(currPos)});

  // Base Case: If all vertices are visited
  if (numVisited == numVertices) {
    // Find the cost to return to the starting vertex (0)
    int returnCost = graph.GetEdgeWeight(currPos, 0);

    events.push_back({currPath, visited, currCost, minCost, bestPath, 2, "All visited. Checking return to start. Cost: " + std::to_string(returnCost)});

    // If there's a valid edge back and the total cost is strictly better
    if (returnCost > 0 && currCost + returnCost < minCost) {
      minCost = currCost + returnCost;
      bestPath = currPath;
      bestPath.push_back(
          0); // Add the start node to the end to complete the cycle
          
      events.push_back({currPath, visited, currCost, minCost, bestPath, 3, "New best path found! Cost: " + std::to_string(minCost)});
    }
    return;
  }

  // Recursive Step: Try visiting all other unvisited vertices
  for (int i = 0; i < numVertices; i++) {
    if (!visited[i]) {
      int edgeWeight = graph.GetEdgeWeight(currPos, i);

      events.push_back({currPath, visited, currCost, minCost, bestPath, 4, "Checking edge " + std::to_string(currPos) + " -> " + std::to_string(i)});

      // Only proceed if there is an actual edge connecting them
      if (edgeWeight > 0) {
        // 1. Choose
        visited[i] = true;
        currPath.push_back(i);
        
        events.push_back({currPath, visited, currCost, minCost, bestPath, 5, "Choosing edge " + std::to_string(currPos) + " -> " + std::to_string(i)});

        // 2. Explore (Recurse deeper)
        TSP_Backtrack_Helper(graph, i, numVisited + 1, currCost + edgeWeight,
                             currPath, visited, minCost, bestPath, events);

        // 3. Un-choose (Backtrack)
        visited[i] = false;
        currPath.pop_back();
        
        events.push_back({currPath, visited, currCost, minCost, bestPath, 6, "Backtracking from " + std::to_string(i)});
      }
    }
  }
}

// The main function that initializes variables and calls the helper
TSPResult TSP_BruteForce(const Graph &graph) {
  TSPResult result;
  int numVertices = graph.GetVertexCount();

  // Safety check for empty graphs
  if (numVertices == 0) {
    result.totalCost = 0;
    return result;
  }

  // Initialization
  std::vector<bool> visited(numVertices, false);
  std::vector<int> currPath;
  std::vector<int> bestPath;
  int minCost = std::numeric_limits<int>::max(); // Start with "infinity"

  // Always start the path from vertex 0
  visited[0] = true;
  currPath.push_back(0);
  std::vector<VisualizationEvent> events;

  // Call the recursive helper
  TSP_Backtrack_Helper(graph, 0, 1, 0, currPath, visited, minCost, bestPath, events);

  // Save results
  result.path = bestPath;
  // If minCost is still infinity, no path was found (disconnected graph)
  result.totalCost = (minCost == std::numeric_limits<int>::max()) ? 0 : minCost;
  result.events = events;

  return result;
}

TSPResult TSP_LocalSearch2Opt(const Graph &graph) {
  TSPResult result;
  int n = graph.GetVertexCount();
  std::vector<VisualizationEvent> events;

  if (n == 0) {
    result.totalCost = 0;
    result.events = events;
    return result;
  }

  std::vector<int> currentTour = BuildInitialRandomTour(graph);
  if (currentTour.empty()) {
    PushEvent(events, graph, {}, 0, 0, {}, 1,
              "Could not build an initial valid tour.");
    result.path = {};
    result.totalCost = 0;
    result.events = events;
    return result;
  }

  int currentCost = CalculatePathCost(graph, currentTour);
  int bestCost = currentCost;
  std::vector<int> bestTour = currentTour;

  PushEvent(events, graph, currentTour, currentCost, bestCost, bestTour, 1,
            "Build random initial tour.");

  bool improved = true;
  while (improved) {
    improved = false;
    PushEvent(events, graph, currentTour, currentCost, bestCost, bestTour, 2,
              "Scan all 2-opt swaps.");

    for (int i = 1; i < n - 1 && !improved; ++i) {
      for (int j = i + 1; j < n && !improved; ++j) {
        std::vector<int> candidate = currentTour;
        std::reverse(candidate.begin() + i, candidate.begin() + j + 1);

        int candidateCost = CalculatePathCost(graph, candidate);
        PushEvent(events, graph, candidate, candidateCost, bestCost, bestTour,
                  3, "Try swap between i=" + std::to_string(i) +
                         " and j=" + std::to_string(j) + ".");

        if (candidateCost < currentCost) {
          currentTour = candidate;
          currentCost = candidateCost;
          improved = true;

          if (currentCost < bestCost) {
            bestCost = currentCost;
            bestTour = currentTour;
          }

          PushEvent(events, graph, currentTour, currentCost, bestCost,
                    bestTour, 4,
                    "Accept improving swap. New cost: " +
                        std::to_string(currentCost));
        }
      }
    }
  }

  PushEvent(events, graph, bestTour, bestCost, bestCost, bestTour, 5,
            "No improving swap left. Stop.");

  result.path = bestTour;
  result.totalCost = bestCost;
  result.events = events;
  return result;
}
