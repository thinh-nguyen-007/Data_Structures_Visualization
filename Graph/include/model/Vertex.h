#pragma once
#include "raylib.h"
#include <utility>
class Vertex {
  friend class Graph;

private:
  Vector2 location;
  int idx;
  Color color;
  Vector2 velocity;

public:
  Vertex();
  Vertex(Vector2 location, int idx);
  int x = location.x;
  int y = location.y;
};