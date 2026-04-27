#include "InputHandler.h"
#include "Algorithms.h"
#include "Visualizer.h"
#include <cstdlib> // For atoi
#include <cstring> // For strncpy
// WARNING: You must define this EXACTLY ONCE before including raygui!
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
// Initialize variables and pass the Graph reference
InputHandler::InputHandler(Graph &graphRef, Visualizer *vis)
    : graph(graphRef), visualizer(vis) {
  showMenu = false;
  textBoxEditMode = false;
  nodeCountEditMode = false;
  showBruteForceSizeWarning = false;
  darkMode = false;

// Set a default string so you don't have to type it every time
#pragma warning(disable : 4996)
  strncpy(textBuffer, "matrix.txt", 256);
  strncpy(nodeCountBuffer, "8", 16);
}
void InputHandler::Update() {}
void InputHandler::Draw() {
  // 1. The Main "Input Graph" toggle button
  if (GuiButton({20, 20, 200, 50}, "Input Graph")) {
    showMenu = !showMenu;
  }
  // --- NEW: Run TSP Button ---
  if (GuiButton({240, 20, 240, 50}, "Run Brute Force TSP")) {
    int nodeCount = graph.GetVertexCount();
    if (nodeCount > 7) {
      showBruteForceSizeWarning = true;
    } else {
      showBruteForceSizeWarning = false;
      auto result = TSP_BruteForce(graph);

      std::vector<std::string> pseudoCode = {
          "1. If all nodes visited: check return to start",
          "2. If valid return path and cost < bestCost:",
          "3.    Update bestCost and bestPath",
          "4. For each unvisited neighbor V:",
          "5.    Choose edge, mark V visited",
          "6.    Recurse deeper (un-choose when done)"};

      if (visualizer) {
        visualizer->SetResult(result, pseudoCode);
      }

      graph.SetTSPPath(result.path); // Highlights the path!
    }
  }

  if (showBruteForceSizeWarning) {
    DrawText("The graph is too large (> 7). Consider drawing smaller graph",
             240, 75, 24, RED);
  }

  if (GuiButton({500, 20, 220, 50}, "Run 2-opt TSP")) {
    auto result = TSP_LocalSearch2Opt(graph);

    std::vector<std::string> pseudoCode = {
        "1. Build an initial random valid tour",
        "2. While we find an improvement",
        "3.    Try to swap every pair of edges",
        "4.    If the swap improves cost , accept it",
        "5. Return best tour found"};

    if (visualizer) {
      visualizer->SetResult(result, pseudoCode);
    }

    graph.SetTSPPath(result.path);
  }
  // ---------------------------

  // 2. Only draw the sub-menu if it's open
  if (showMenu) {
    // Draw background panel
    GuiPanel({20, 90, 470, 200}, "Graph Generators");

    // Random graph row: Random graph [input] nodes [Generate]
    DrawText("Random graph", 40, 155, 20, DARKGRAY);
    if (GuiTextBox({190, 145, 50, 40}, nodeCountBuffer, 35,
                   nodeCountEditMode)) {
      nodeCountEditMode = !nodeCountEditMode;
    }
    DrawText("nodes", 265, 155, 20, DARKGRAY);
    if (GuiButton({330, 145, 140, 50}, "Generate")) {
      int n = atoi(nodeCountBuffer);
      if (n >= 2) {
        auto randomMat = graph.GenerteRandomMatrix(n);
        graph.LoadFromMatrix(randomMat);
        if (visualizer) visualizer->Stop();
        showBruteForceSizeWarning = false;
        showMenu = false;
      }
    }
    // Text Box for your filename
    if (GuiTextBox({40, 210, 300, 50}, textBuffer, 256, textBoxEditMode)) {
      textBoxEditMode =
          !textBoxEditMode; // Lock/Unlock typing mode when clicked
    }
    // Load Matrix Button!
    if (GuiButton({360, 210, 110, 50}, "Load File")) {
      auto fileMat = graph.getMatrix(std::string(textBuffer));
      int n = (int)fileMat.size();
      if (!fileMat.empty() && n >= 2) {
        graph.LoadFromMatrix(fileMat);
        if (visualizer) visualizer->Stop();
        showBruteForceSizeWarning = false;
      }
      showMenu = false;
    }
  }

  // Dark Mode Toggle Button (Top Right)
  if (GuiButton({(float)GetScreenWidth() - 140, 20, 120, 50},
                darkMode ? "Light Mode" : "Dark Mode")) {
    darkMode = !darkMode;
  }
}