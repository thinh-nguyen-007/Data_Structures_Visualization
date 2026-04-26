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
  darkMode = false;

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

    // Row of vertex count buttons (2 to 7)
    DrawText("Nodes:", 40, 150, 20, DARKGRAY);
    float btnStartX = 120.0f;
    float btnWidth = 55.0f;
    float btnGap = 5.0f;
    for (int n = 2; n <= 7; n++) {
      float x = btnStartX + (n - 2) * (btnWidth + btnGap);
      if (GuiButton({x, 140, btnWidth, 50}, TextFormat("%d", n))) {
        auto randomMat = graph.GenerteRandomMatrix(n);
        graph.LoadFromMatrix(randomMat);
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
      if (!fileMat.empty()) {
        graph.LoadFromMatrix(fileMat);
      }
      showMenu = false;
    }
  }

  // Dark Mode Toggle Button (Top Right)
  if (GuiButton({(float)GetScreenWidth() - 140, 20, 120, 50}, darkMode ? "Light Mode" : "Dark Mode")) {
      darkMode = !darkMode;
  }
}