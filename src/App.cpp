#include "App.h"

App::App(int width, int height, const char *title)
    : screenWidth(width), screenHeight(height),
      inputHandler(graph, &visualizer) {
  // Initialize the window here. This ensures Raylib is ready as soon as App is
  // created.
  InitWindow(screenWidth, screenHeight, title);
  SetTargetFPS(60);

  visualizer.Init();

  auto randomMat = graph.GenerteRandomMatrix(6);
  graph.LoadFromMatrix(randomMat);
}

App::~App() {
  // Cleans up the window when the App goes out of scope.
  CloseWindow();
}

void App::Run() {
  // The core application loop
  while (!WindowShouldClose()) {
    Update(); // 1. Update data/logic
    Draw();   // 2. Render to screen
  }
}

void App::Update() {
  // TODO: We will put our InputHandler checks and Graph data updates here
  graph.Update();
  inputHandler.Update();
  visualizer.Update();
}

void App::Draw() {
  BeginDrawing();

  ClearBackground(RAYWHITE); // Using RAYWHITE for a cleaner look

  if (visualizer.IsActive()) {
    visualizer.Draw(graph, screenWidth, screenHeight);
  } else {
    graph.Draw();
  }

  inputHandler.Draw();
  EndDrawing();
}
