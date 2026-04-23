#include "Edge.h"

Edge::Edge() {}

Edge::Edge(int u, int v, int w) {
  idx.first = u;
  idx.second = v;
  weight = w;
  color = DARKGRAY;
}
