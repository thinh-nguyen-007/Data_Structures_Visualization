#ifndef APP_H
#define APP_H

#include "Algorithms.h"
#include "core/Graph.h"
#include "UI/Visualizer.h"
#include "UI/InputHandler.h"
#include "raylib.h"
#include <string>

namespace GraphApp {

class App {
public:
  // resourcePath allows external entry points to specify where assets/ are located
  App(int width, int height, const char *title, const std::string& resourcePath = "");
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
  Camera2D camera;
  Font appFont;
  Font descFont;
  std::string baseDir;
};

} // namespace GraphApp

#endif // APP_H
