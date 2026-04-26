#include "Graph.h"
#include "Algorithms.h"

Graph::Graph() {}
Graph::~Graph() {}

void Graph::Init() {}

void Graph::Draw(const VisualizationEvent *event, bool isDarkMode) {
  // 1. Draw Edges
  for (const auto &edge : edges) {
    // Get the coordinates from the connected vertices
    Vector2 startPos = vertices[edge.idx.first].location;
    Vector2 endPos = vertices[edge.idx.second].location;

    // Check if this edge is part of the TSP path
    bool isTSP = false;
    bool isExploring = false;

    if (!event && currentTSPPath.size() > 1) {
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

    if (event && event->currentPath.size() > 1) {
      for (size_t i = 0; i < event->currentPath.size() - 1; i++) {
        int u = event->currentPath[i];
        int v = event->currentPath[i + 1];
        if (edge.idx.first == u && edge.idx.second == v) {
          isExploring = true;
          break;
        }
      }
    }

    Color defaultEdgeColor = isDarkMode ? RAYWHITE : edge.color;
    Color edgeColor = isTSP ? GREEN : (isExploring ? ORANGE : defaultEdgeColor);
    float edgeThickness = isTSP || isExploring ? 8.0f : 4.0f;

    // Check if reverse edge exists
    bool hasReverse = false;
    for (const auto &other : edges) {
      if (other.idx.first == edge.idx.second &&
          other.idx.second == edge.idx.first) {
        hasReverse = true;
        break;
      }
    }

    float angle = atan2(endPos.y - startPos.y, endPos.x - startPos.x);

    float shiftAmount = hasReverse ? 10.0f : 0.0f;
    if (hasReverse) {
      startPos.x -= sin(angle) * shiftAmount;
      startPos.y += cos(angle) * shiftAmount;
      endPos.x -= sin(angle) * shiftAmount;
      endPos.y += cos(angle) * shiftAmount;
    }

    // Draw the connecting line
    DrawLineEx(startPos, endPos, edgeThickness, edgeColor);

    // Position arrowhead exactly on the border of the destination vertex (radius 50)
    // We use the Pythagorean theorem because the line is shifted sideways
    float radius = 50.0f;
    float setback = sqrt(radius * radius - shiftAmount * shiftAmount);
    Vector2 arrowPos = {endPos.x - cos(angle) * setback,
                        endPos.y - sin(angle) * setback};

    // Draw the arrowhead (a triangle)
    float arrowSize = 20.0f; // Increased arrow size for better visibility
    float pi = 3.14159f;
    Vector2 p1 = {arrowPos.x - cos(angle - pi / 6.0f) * arrowSize,
                  arrowPos.y - sin(angle - pi / 6.0f) * arrowSize};
    Vector2 p2 = {arrowPos.x - cos(angle + pi / 6.0f) * arrowSize,
                  arrowPos.y - sin(angle + pi / 6.0f) * arrowSize};

    // Swap p1 and p2 to fix potential winding order issues (counter-clockwise
    // required in Raylib)
    DrawTriangle(arrowPos, p2, p1, edgeColor);

    // Draw the weight text shifted 50% along the line to be in the middle
    int textX = startPos.x + (endPos.x - startPos.x) * 0.5f;
    int textY = startPos.y + (endPos.y - startPos.y) * 0.5f;
    Color weightColor = isDarkMode ? RAYWHITE : DARKGRAY;
    DrawText(TextFormat("%d", edge.weight), textX, textY - 20, 20,
             isTSP || isExploring ? edgeColor : weightColor);
  }

  // 2. Draw Vertices
  for (const auto &vertex : vertices) {
    Color defaultVColor = isDarkMode ? DARKGRAY : RAYWHITE;
    Color vColor = defaultVColor;
    if (event && event->visited.size() > vertex.idx &&
        event->visited[vertex.idx]) {
      vColor = ORANGE; // Highlight visited nodes
    }

    // Draw the colored circle (acts as an eraser over edges)
    DrawCircleV(vertex.location, 45.0f, vColor);

    // Draw a nice outline using DrawRing
    Color borderColor = isDarkMode ? RAYWHITE : BLACK;
    DrawRing(vertex.location, 45.0f, 50.0f, 0.0f, 360.0f, 100, borderColor);

    // Draw the vertex ID inside the circle
    Color textColor = isDarkMode ? RAYWHITE : BLACK;
    const char* text = TextFormat("%d", vertex.idx);
    int textWidth = MeasureText(text, 50);
    DrawText(text, vertex.location.x - textWidth/2, vertex.location.y - 25, 50, textColor);
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
  const float REPULSION_CONSTANT = 80000.0f; // Push much harder to spread large nodes
  const float ATTRACTION_CONSTANT = 0.00005f; // Looser springs
  const float GRAVITY = 0.01f;             // Gentle pull to center
  const float DAMPING = 0.9f;
  const float MAX_SPEED = 15.0f; // Higher speed limit

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

void Graph::SetTSPPath(const std::vector<int> &path) { currentTSPPath = path; }

int Graph::GetEdgeWeight(int u, int v) const {
  if (u >= 0 && u < adjacencyMatrix.size() && v >= 0 &&
      v < adjacencyMatrix.size()) {
    return adjacencyMatrix[u][v];
  }
  return 0;
}

int Graph::GetVertexCount() const { return vertices.size(); }
