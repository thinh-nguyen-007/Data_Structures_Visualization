#pragma once
#include "Edge.h"
#include "Vertex.h"
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

public:
  Graph();
  ~Graph();

  void Draw();
  void Update();
  void HandleInput();

  void Init();
  void Shutdown();

  void Clear();

  void LoadFromMatrix(const std::vector<std::vector<int>> &matrix);
  std::vector<std::vector<int>> GenerteRandomMatrix(int numVertices);
  std::vector<std::vector<int>> getMatrix(const std::string &filename);

  int screenWidth = 800;
  int screenHeight = 600;
};