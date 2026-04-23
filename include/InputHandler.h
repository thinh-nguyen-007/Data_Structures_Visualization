#pragma once
#include "Graph.h"
#include "raylib.h"
#include <string>

class InputHandler {
private:
  Graph &graph;
  bool showMenu;        // Toggles the drop-down panel
  char textBuffer[256]; // Holds your filename
  bool textBoxEditMode; // Is the textbox currently being typed in?
public:
  InputHandler(Graph &graphRef);
  void Update();
  void Draw();
};