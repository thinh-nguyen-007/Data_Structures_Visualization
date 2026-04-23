#include "InputHandler.h"
#include "Algorithms.h"
#include <cstring> // For strncpy
// WARNING: You must define this EXACTLY ONCE before including raygui!
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
// Initialize variables and pass the Graph reference
InputHandler::InputHandler(Graph &graphRef) : graph(graphRef) {
  showMenu = false;
  textBoxEditMode = false;

// Set a default string so you don't have to type it every time
#pragma warning(disable : 4996)
  strncpy(textBuffer, "matrix.txt", 256);
}
void InputHandler::Update() {}
void InputHandler::Draw() {
  // 1. The Main "Input Graph" toggle button
  if (GuiButton({10, 10, 120, 30}, "Input Graph")) {
    showMenu = !showMenu;
  }
  // --- NEW: Run TSP Button ---
  if (GuiButton({140, 10, 160, 30}, "Run Brute Force TSP")) {
      auto result = TSP_BruteForce(graph);
      graph.SetTSPPath(result.path); // Highlights the path!
  }
  // ---------------------------

  // 2. Only draw the sub-menu if it's open
  if (showMenu) {
    // Draw background panel
    GuiPanel({10, 50, 260, 130}, "Graph Generators");
    // Random Button!
    if (GuiButton({20, 80, 240, 30}, "Generate Random Graph (5 Nodes)")) {
      auto randomMat = graph.GenerteRandomMatrix(5);
      graph.LoadFromMatrix(randomMat);
      showMenu = false;
    }
    // Text Box for your filename
    if (GuiTextBox({20, 120, 160, 30}, textBuffer, 256, textBoxEditMode)) {
      textBoxEditMode =
          !textBoxEditMode; // Lock/Unlock typing mode when clicked
    }
    // Load Matrix Button!
    if (GuiButton({190, 120, 70, 30}, "Load File")) {
      auto fileMat = graph.getMatrix(std::string(textBuffer));
      if (!fileMat.empty()) {
        graph.LoadFromMatrix(fileMat);
      }
      showMenu = false;
    }
  }
}