#include "Algorithms.h"
#include "Graph.h"
#include <limits> // Required for std::numeric_limits
#include <string>

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
