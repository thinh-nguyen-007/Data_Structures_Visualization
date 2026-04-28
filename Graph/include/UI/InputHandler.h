#pragma once
#include "core/Graph.h"
#include "raylib.h"
#include <string>

class Visualizer; // Forward declaration

class InputHandler {
private:
  Graph &graph;
  Visualizer* visualizer;
  bool showMenu;        // Toggles the drop-down panel
  char textBuffer[256]; // Holds your filename
  bool textBoxEditMode; // Is the textbox currently being typed in?
  char nodeCountBuffer[16];
  bool nodeCountEditMode;
  bool showBruteForceSizeWarning;
  float bruteForceSizeWarningTimer;
  bool darkMode;
public:
  bool IsDarkMode() const { return darkMode; }
  InputHandler(Graph &graphRef, Visualizer* vis);
  void Update();
  void Draw();
};