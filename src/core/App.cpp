#include "App.h"

App::App(int width, int height, const char *title)
    : screenWidth(width), screenHeight(height) {
  // Initialize the window here. This ensures Raylib is ready as soon as App is
  // created.
  InitWindow(screenWidth, screenHeight, title);
  SetTargetFPS(60);

  auto randomMat = graph.GenerteRandomMatrix(10);
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
}

void App::Draw() {
  BeginDrawing();

  ClearBackground(GRAY);

  // A simple text to verify our App loop is running
  graph.Draw();
  EndDrawing();
}
