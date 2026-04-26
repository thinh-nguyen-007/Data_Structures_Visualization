#include "Graph.h"
#include "Algorithms.h"

Graph::Graph() {}
Graph::~Graph() {}

void Graph::Init(Font font) { customFont = font; }

void Graph::Draw(const VisualizationEvent *event, bool isDarkMode) {
  // 1. Draw Edge lines and arrowheads (first pass)
  for (const auto &edge : edges) {
    Vector2 startPos = vertices[edge.idx.first].location;
    Vector2 endPos = vertices[edge.idx.second].location;

    bool isTSP = false;
    bool isExploring = false;

    if (!event && currentTSPPath.size() > 1) {
      for (size_t i = 0; i < currentTSPPath.size() - 1; i++) {
        int u = currentTSPPath[i];
        int v = currentTSPPath[i + 1];
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

    DrawLineEx(startPos, endPos, edgeThickness, edgeColor);

    float radius = 50.0f;
    float setback = sqrt(radius * radius - shiftAmount * shiftAmount);
    Vector2 arrowPos = {endPos.x - cos(angle) * setback,
                        endPos.y - sin(angle) * setback};

    float arrowSize = 20.0f;
    float pi = 3.14159f;
    Vector2 p1 = {arrowPos.x - cos(angle - pi / 6.0f) * arrowSize,
                  arrowPos.y - sin(angle - pi / 6.0f) * arrowSize};
    Vector2 p2 = {arrowPos.x - cos(angle + pi / 6.0f) * arrowSize,
                  arrowPos.y - sin(angle + pi / 6.0f) * arrowSize};

    DrawTriangle(arrowPos, p2, p1, edgeColor);
  }

  // 2. Draw Edge weight labels (second pass - always on top of all edges)
  for (const auto &edge : edges) {
    Vector2 startPos = vertices[edge.idx.first].location;
    Vector2 endPos = vertices[edge.idx.second].location;

    bool isTSP = false;
    bool isExploring = false;
    if (!event && currentTSPPath.size() > 1) {
      for (size_t i = 0; i < currentTSPPath.size() - 1; i++) {
        if (edge.idx.first == currentTSPPath[i] &&
            edge.idx.second == currentTSPPath[i + 1]) {
          isTSP = true;
          break;
        }
      }
    }
    if (event && event->currentPath.size() > 1) {
      for (size_t i = 0; i < event->currentPath.size() - 1; i++) {
        if (edge.idx.first == event->currentPath[i] &&
            edge.idx.second == event->currentPath[i + 1]) {
          isExploring = true;
          break;
        }
      }
    }

    Color defaultEdgeColor = isDarkMode ? RAYWHITE : edge.color;
    Color edgeColor = isTSP ? GREEN : (isExploring ? ORANGE : defaultEdgeColor);

    float angle = atan2(endPos.y - startPos.y, endPos.x - startPos.x);

    // Check if reverse edge exists
    bool hasReverse = false;
    for (const auto &other : edges) {
      if (other.idx.first == edge.idx.second &&
          other.idx.second == edge.idx.first) {
        hasReverse = true;
        break;
      }
    }

    float labelT = 0.3f;
    float midX = startPos.x + (endPos.x - startPos.x) * labelT;
    float midY = startPos.y + (endPos.y - startPos.y) * labelT;
    // Offset perpendicular to match the shifted edge line direction
    float perpOffset = hasReverse ? 30.0f : 0.0f;
    int textX = (int)(midX - sin(angle) * perpOffset);
    int textY = (int)(midY + cos(angle) * perpOffset);
    Color weightColor = isDarkMode ? RAYWHITE : BLACK;
    Color finalColor = isTSP || isExploring ? edgeColor : weightColor;
    const char *weightText = TextFormat("%d", edge.weight);
    // Use custom font for edge weight labels
    DrawTextEx(customFont, weightText, {(float)textX, (float)textY}, 36, 1,
               finalColor);
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
    const char *text = TextFormat("%d", vertex.idx);
    float fontSize = 50.0f;
    Vector2 textSize = MeasureTextEx(customFont, text, fontSize, 1);
    // Center horizontally using measured width, vertically center using
    // measured height
    float textX = vertex.location.x - textSize.x / 2.0f;
    float textY = vertex.location.y - fontSize * 0.5f;
    DrawTextEx(customFont, text, {textX, textY}, fontSize, 1, textColor);
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
                                       std::vector<int>(numVertices, 0));
  // ~30% chance of generating a complete graph
  bool makeComplete = (GetRandomValue(1, 100) <= 30);

  if (makeComplete) {
    for (int i = 0; i < numVertices; i++) {
      for (int j = 0; j < numVertices; j++) {
        if (i != j)
          matrix[i][j] = GetRandomValue(1, 100);
      }
    }
  } else {
    // Guarantee a Hamiltonian cycle so TSP is always solvable
    std::vector<int> order(numVertices);
    for (int i = 0; i < numVertices; i++)
      order[i] = i;
    for (int i = numVertices - 1; i > 0; i--) {
      int j = GetRandomValue(0, i);
      std::swap(order[i], order[j]);
    }
    for (int i = 0; i < numVertices; i++) {
      int from = order[i];
      int to = order[(i + 1) % numVertices];
      matrix[from][to] = GetRandomValue(1, 100);
      matrix[to][from] = GetRandomValue(1, 100);
    }
    // Randomly add extra edges (~60% chance each)
    for (int i = 0; i < numVertices; i++) {
      for (int j = 0; j < numVertices; j++) {
        if (i != j && matrix[i][j] == 0 && GetRandomValue(1, 100) <= 40) {
          matrix[i][j] = GetRandomValue(1, 100);
        }
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
  const float REPULSION_CONSTANT =
      80000.0f; // Push much harder to spread large nodes
  const float ATTRACTION_CONSTANT = 0.00005f; // Looser springs
  const float GRAVITY = 0.01f;                // Gentle pull to center
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
