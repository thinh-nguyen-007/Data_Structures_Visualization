#include "Graph.h"

Graph::Graph() {}
Graph::~Graph() {}

void Graph::Init() {}

void Graph::Draw() {
  // 1. Draw Edges
  for (const auto &edge : edges) {
    // Get the coordinates from the connected vertices
    Vector2 startPos = vertices[edge.idx.first].location;
    Vector2 endPos = vertices[edge.idx.second].location;

    // Check if this edge is part of the TSP path
    bool isTSP = false;
    if (currentTSPPath.size() > 1) {
        for (size_t i = 0; i < currentTSPPath.size() - 1; i++) {
            int u = currentTSPPath[i];
            int v = currentTSPPath[i + 1];
            // STRICT DIRECTION CHECK for directed graphs
            if (edge.idx.first == u && edge.idx.second == v) {
                isTSP = true;
                break;
            }
        }
    }

    Color edgeColor = isTSP ? RED : edge.color;
    float edgeThickness = isTSP ? 8.0f : 4.0f;

    // Draw the connecting line
    DrawLineEx(startPos, endPos, edgeThickness, edgeColor);

    // Calculate angle for arrowhead
    float angle = atan2(endPos.y - startPos.y, endPos.x - startPos.x);
    
    // Position arrowhead at the edge of the destination vertex (radius is 20)
    Vector2 arrowPos = {
        endPos.x - cos(angle) * 20.0f,
        endPos.y - sin(angle) * 20.0f
    };
    
    // Draw the arrowhead (a triangle)
    float arrowSize = 15.0f;
    float pi = 3.14159f;
    Vector2 p1 = { arrowPos.x - cos(angle - pi/6.0f) * arrowSize, arrowPos.y - sin(angle - pi/6.0f) * arrowSize };
    Vector2 p2 = { arrowPos.x - cos(angle + pi/6.0f) * arrowSize, arrowPos.y - sin(angle + pi/6.0f) * arrowSize };
    DrawTriangle(arrowPos, p1, p2, edgeColor);

    // Draw the weight text shifted 75% along the line so bidirectional weights don't overlap
    int textX = startPos.x + (endPos.x - startPos.x) * 0.75f;
    int textY = startPos.y + (endPos.y - startPos.y) * 0.75f;
    DrawText(TextFormat("%d", edge.weight), textX, textY - 20, 20, isTSP ? RED : DARKGRAY);
  }

  // 2. Draw Vertices
  for (const auto &vertex : vertices) {
    // Draw the colored circle
    DrawCircleV(vertex.location, 20.0f, vertex.color);

    // Draw a nice black outline
    DrawCircleLines(vertex.location.x, vertex.location.y, 20.0f, DARKBROWN);

    // Draw the vertex ID inside the circle
    DrawText(TextFormat("%d", vertex.idx), vertex.location.x - 5,
             vertex.location.y - 10, 20, WHITE);
  }
}

void Graph::Clear() {
  vertices.clear();
  edges.clear();
}

void Graph::LoadFromMatrix(const std::vector<std::vector<int>> &matrix) {
  Clear();
  int n = matrix.size();
  if (n == 0 || matrix[0].size() != n) {
    std::cout << "Invalid matrix" << std::endl;
    return;
  }

  adjacencyMatrix = matrix;
  currentTSPPath.clear();

  for (int i = 0; i < n; i++) {
    float scatterX = screenWidth / 2 + GetRandomValue(-150, 150);
    float scatterY = screenHeight / 2 + GetRandomValue(-150, 150);
    vertices.push_back(Vertex({scatterX, scatterY}, i));
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      int weight = matrix[i][j];
      if (i != j && weight > 0) {
        edges.push_back(Edge(i, j, weight));
      }
    }
  }
}

std::vector<std::vector<int>> Graph::GenerteRandomMatrix(int numVertices) {
  std::vector<std::vector<int>> matrix(numVertices,
                                       std::vector<int>(numVertices));
  for (int i = 0; i < numVertices; i++) {
    for (int j = 0; j < numVertices; j++) {
      if (i != j) {
        matrix[i][j] = GetRandomValue(1, 100);
      } else {
        matrix[i][j] = 0;
      }
    }
  }
  return matrix;
}

std::vector<std::vector<int>> Graph::getMatrix(const std::string &filename) {
  std::vector<std::vector<int>> matrix;
  std::ifstream fin(filename);

  if (fin.is_open()) {
    // Get the number of vertices first
    int numVertices;
    fin >> numVertices;

    matrix.resize(numVertices, std::vector<int>(numVertices));

    for (int i = 0; i < numVertices; i++) {
      for (int j = 0; j < numVertices; j++) {
        fin >> matrix[i][j];
      }
    }
    fin.close();
  }

  return matrix;
}

void Graph::Update() {
  // Tweak these constants to make your graph behave differently!
  const float REPULSION_CONSTANT = 5000.0f; // Push hard!
  const float ATTRACTION_CONSTANT = 0.0001f; // Super loose springs
  const float GRAVITY = 0.01f;             // Gentle pull to center
  const float DAMPING = 0.85f;  
  const float MAX_SPEED = 15.0f;           // Higher speed limit

  Vector2 center = {screenWidth / 2.0f,
                    screenHeight / 2.0f}; // Center of the screen

  // 1. REPULSION (Nodes push each other away like opposite magnets)
  for (int i = 0; i < vertices.size(); i++) {
    for (int j = i + 1; j < vertices.size(); j++) {
      float dx = vertices[i].location.x - vertices[j].location.x;
      float dy = vertices[i].location.y - vertices[j].location.y;
      float distance = sqrt(dx * dx + dy * dy);
      if (distance > 0.1f) {
        // Force gets weaker the further away they are
        float force = REPULSION_CONSTANT / distance;
        float forceX = (dx / distance) * force;
        float forceY = (dy / distance) * force;
        vertices[i].velocity.x += forceX;
        vertices[i].velocity.y += forceY;
        vertices[j].velocity.x -= forceX;
        vertices[j].velocity.y -= forceY;
      }
    }
  }

  // 2. ATTRACTION (Edges act like rubber bands pulling connected nodes)
  for (const auto &edge : edges) {
    int u = edge.idx.first;
    int v = edge.idx.second;
    float dx = vertices[v].location.x - vertices[u].location.x;
    float dy = vertices[v].location.y - vertices[u].location.y;
    float distance = sqrt(dx * dx + dy * dy);
    // Force grows stronger the further they are stretched
    float force = ATTRACTION_CONSTANT * (distance * distance);
    float forceX = (dx / distance) * force;
    float forceY = (dy / distance) * force;
    vertices[u].velocity.x += forceX;
    vertices[u].velocity.y += forceY;
    vertices[v].velocity.x -= forceX;
    vertices[v].velocity.y -= forceY;
  }

  // 3. APPLY FORCES, SPEED LIMITS & DAMPING
  for (auto &vertex : vertices) {
    // Gravity
    vertex.velocity.x += (center.x - vertex.location.x) * GRAVITY;
    vertex.velocity.y += (center.y - vertex.location.y) * GRAVITY;
    // --- NEW: THE SPEED LIMIT MATH ---
    // If our velocity is higher than MAX_SPEED, scale it back down!
    float speed = sqrt(vertex.velocity.x * vertex.velocity.x +
                       vertex.velocity.y * vertex.velocity.y);
    if (speed > MAX_SPEED) {
      vertex.velocity.x = (vertex.velocity.x / speed) * MAX_SPEED;
      vertex.velocity.y = (vertex.velocity.y / speed) * MAX_SPEED;
    }
    // ---------------------------------
    // Apply Velocity to Position
    vertex.location.x += vertex.velocity.x;
    vertex.location.y += vertex.velocity.y;

    // Apply Damping
    vertex.velocity.x *= DAMPING;
    vertex.velocity.y *= DAMPING;
  }
}

void Graph::HandleInput() {}
void Graph::Shutdown() {}

void Graph::SetTSPPath(const std::vector<int>& path) {
    currentTSPPath = path;
}

int Graph::GetEdgeWeight(int u, int v) const {
    if (u >= 0 && u < adjacencyMatrix.size() && v >= 0 && v < adjacencyMatrix.size()) {
        return adjacencyMatrix[u][v];
    }
    return 0;
}

int Graph::GetVertexCount() const {
    return vertices.size();
}
