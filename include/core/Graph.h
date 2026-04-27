#pragma once
#include "Edge.h"
#include "Vertex.h"
#include "raygui.h"
#include "raylib.h"
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

class Graph {
private:
  std::vector<Vertex> vertices;
  std::vector<Edge> edges;
  std::vector<std::vector<int>> adjacencyMatrix;
  std::vector<int> currentTSPPath;
  Font customFont;

public:
  Graph();
  ~Graph();

  void Draw(const struct VisualizationEvent* event = nullptr, bool isDarkMode = false);
  void Update();
  void HandleInput();

  void Init(Font font);
  void Shutdown();

  void Clear();

  void LoadFromMatrix(const std::vector<std::vector<int>> &matrix);
  std::vector<std::vector<int>> GenerteRandomMatrix(int numVertices);
  std::vector<std::vector<int>> getMatrix(const std::string &filename);

  // TSP Support Methods
  void SetTSPPath(const std::vector<int> &path);
  int GetEdgeWeight(int u, int v) const;
  int GetVertexCount() const;

  int screenWidth = 1920;
  int screenHeight = 1080;
};