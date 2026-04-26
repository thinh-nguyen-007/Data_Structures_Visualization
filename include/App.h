#ifndef APP_H
#define APP_H

#include "Algorithms.h"
#include "Graph.h"
#include "Visualizer.h"
#include "InputHandler.h"
#include "raylib.h"

class App {
public:
  App(int width, int height, const char *title);
  ~App();

  int screenWidth;
  int screenHeight;

  // Starts the main application loop
  void Run();

private:
  // Handles logic and data updates every frame
  void Update();
  // Graphics rendering every frame
  void Draw();

  Graph graph;
  Visualizer visualizer;
  InputHandler inputHandler;
};

#endif // APP_H
