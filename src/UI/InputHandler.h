#pragma once
#include "../Logic/Graph.h"
#include "raylib.h"
#include <string>

class InputHandler {
private:
  Graph &graph;
  bool showMenu;        // Toggles the drop-down panel
  char textBuffer[256]; // Holds your filename like "matrix.txt"
  bool textBoxEditMode; // Is the textbox currently being typed in?
public:
  InputHandler(Graph &graphRef);
  void Update();
  void Draw();
};