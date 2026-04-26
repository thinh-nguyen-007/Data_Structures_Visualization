#include "Vertex.h"

Vertex::Vertex() {}

Vertex::Vertex(Vector2 location, int idx) {
  this->location = location;
  this->idx = idx;
  this->color = BLUE;
  this->velocity = {0.0f, 0.0f};
}