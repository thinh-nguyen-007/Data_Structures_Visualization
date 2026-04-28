#pragma once
#include "raylib.h"
#include <utility>

class Edge {
  friend class Graph;

private:
  std::pair<int, int> idx; // the index of the connected vertices
  int weight;
  Color color;

public:
  // Constructors
  Edge();
  Edge(int u, int v, int w);
};
