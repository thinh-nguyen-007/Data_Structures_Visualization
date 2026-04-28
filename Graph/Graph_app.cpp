#include "core/App.h"
#include <iostream>

namespace GraphApp {

App::App(int width, int height, const char *title, const std::string& resourcePath)
    : screenWidth(width), screenHeight(height),
      inputHandler(graph, &visualizer), baseDir(resourcePath) {
  
  // Ensure baseDir ends with a slash if not empty
  if (!baseDir.empty() && baseDir.back() != '/' && baseDir.back() != '\\') {
      baseDir += "/";
  }

  // Initialize the window here. This ensures Raylib is ready as soon as App is
  // created.
  InitWindow(screenWidth, screenHeight, title);
  SetTargetFPS(60);

  camera.target = {(float)screenWidth / 2.0f, (float)screenHeight / 2.0f};
  camera.offset = {(float)screenWidth / 2.0f, (float)screenHeight / 2.0f};
  camera.rotation = 0.0f;
  camera.zoom = 1.0f;

  // Load custom font for the entire application
  std::string fontPath1 = baseDir + "assets/Agbalumo-Regular.ttf";
  appFont = LoadFontEx(fontPath1.c_str(), 48, 0, 250);
  if (appFont.texture.id == 0) {
    std::cerr << "Warning: Failed to load font from " << fontPath1 << ". Using default." << std::endl;
    appFont = GetFontDefault(); // Fallback
  }

  // Load ChironGoRound font for the sidepeak description (tracking text)
  std::string fontPath2 = baseDir + "assets/ChironGoRoundTC-VariableFont_wght.ttf";
  descFont = LoadFontEx(fontPath2.c_str(), 48, 0, 250);
  if (descFont.texture.id == 0) {
    std::cerr << "Warning: Failed to load font from " << fontPath2 << ". Using default." << std::endl;
    descFont = GetFontDefault();
  }

  visualizer.Init(appFont, descFont);
  graph.Init(appFont);

  auto randomMat = graph.GenerateRandomMatrix(6);
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

  // --- Camera Panning (Right Mouse Button) ---
  if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
    Vector2 delta = GetMouseDelta();
    // Scale delta by 1/zoom so panning speed matches zoom level
    delta.x = delta.x * (-1.0f / camera.zoom);
    delta.y = delta.y * (-1.0f / camera.zoom);
    camera.target.x += delta.x;
    camera.target.y += delta.y;
  }

  // --- Camera Zooming (Mouse Wheel & Keyboard) ---
  float wheel = GetMouseWheelMove();
  
  // Keyboard zoom shortcuts
  bool ctrlDown = IsKeyDown(KEY_LEFT_CONTROL) || IsKeyDown(KEY_RIGHT_CONTROL);
  if (ctrlDown) {
      if (IsKeyPressed(KEY_EQUAL)) wheel += 1.0f; // + key (usually shared with =)
      if (IsKeyPressed(KEY_MINUS)) wheel -= 1.0f;
  }

  if (wheel != 0) {
    // Get the world point that is under the mouse
    Vector2 mouseWorldPos = GetScreenToWorld2D(GetMousePosition(), camera);
    
    // Set the target to match the mouse position
    camera.offset = GetMousePosition();
    camera.target = mouseWorldPos;
    
    // Scale the zoom
    const float zoomIncrement = 0.125f;
    camera.zoom += (wheel * zoomIncrement);
    
    // Clamp zoom limits
    if (camera.zoom < 0.1f) camera.zoom = 0.1f;
    else if (camera.zoom > 3.0f) camera.zoom = 3.0f;
  }

  // --- Panning Limits ---
  // Prevent the camera target from going too far out into the void
  if (camera.target.x < -2000) camera.target.x = -2000;
  if (camera.target.x > 4000) camera.target.x = 4000;
  if (camera.target.y < -2000) camera.target.y = -2000;
  if (camera.target.y > 3000) camera.target.y = 3000;
}

void App::Draw() {
  BeginDrawing();

  bool isDark = inputHandler.IsDarkMode();
  ClearBackground(isDark ? DARKGRAY : RAYWHITE); 

  BeginMode2D(camera);
  if (visualizer.IsActive()) {
    graph.Draw(visualizer.GetCurrentEvent(), isDark);
  } else {
    graph.Draw(nullptr, isDark);
  }
  EndMode2D();

  // UI drawn outside camera so it doesn't move or scale
  if (visualizer.IsActive()) {
      visualizer.DrawUI(screenWidth, screenHeight);
  }

  inputHandler.Draw();
  EndDrawing();
}

} // namespace GraphApp
