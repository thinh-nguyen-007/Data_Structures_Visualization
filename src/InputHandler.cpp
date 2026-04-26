#include "InputHandler.h"
#include "Algorithms.h"
#include "Visualizer.h"
#include <cstring> // For strncpy
// WARNING: You must define this EXACTLY ONCE before including raygui!
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
// Initialize variables and pass the Graph reference
InputHandler::InputHandler(Graph &graphRef, Visualizer* vis) : graph(graphRef), visualizer(vis) {
  showMenu = false;
  textBoxEditMode = false;

// Set a default string so you don't have to type it every time
#pragma warning(disable : 4996)
  strncpy(textBuffer, "matrix.txt", 256);
}
void InputHandler::Update() {}
void InputHandler::Draw() {
  // 1. The Main "Input Graph" toggle button
  if (GuiButton({20, 20, 200, 50}, "Input Graph")) {
    showMenu = !showMenu;
  }
  // --- NEW: Run TSP Button ---
  if (GuiButton({240, 20, 250, 50}, "Run Brute Force TSP")) {
      auto result = TSP_BruteForce(graph);
      
      std::vector<std::string> pseudoCode = {
          "1. If all nodes visited: check return to start",
          "2. If valid return path and cost < bestCost:",
          "3.   Update bestCost and bestPath",
          "4. For each unvisited neighbor V:",
          "5.   Choose edge, mark V visited",
          "6.   Recurse deeper (un-choose when done)"
      };
      
      if (visualizer) {
          visualizer->SetResult(result, pseudoCode);
      }
      
      graph.SetTSPPath(result.path); // Highlights the path!
  }
  // ---------------------------

  // 2. Only draw the sub-menu if it's open
  if (showMenu) {
    // Draw background panel
    GuiPanel({20, 90, 470, 200}, "Graph Generators");
    // Random Button!
    if (GuiButton({40, 140, 430, 50}, "Generate Random Graph (5 Nodes)")) {
      auto randomMat = graph.GenerteRandomMatrix(5);
      graph.LoadFromMatrix(randomMat);
      showMenu = false;
    }
    // Text Box for your filename
    if (GuiTextBox({40, 210, 300, 50}, textBuffer, 256, textBoxEditMode)) {
      textBoxEditMode =
          !textBoxEditMode; // Lock/Unlock typing mode when clicked
    }
    // Load Matrix Button!
    if (GuiButton({360, 210, 110, 50}, "Load File")) {
      auto fileMat = graph.getMatrix(std::string(textBuffer));
      if (!fileMat.empty()) {
        graph.LoadFromMatrix(fileMat);
      }
      showMenu = false;
    }
  }
}