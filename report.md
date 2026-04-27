# Project Architecture

This project is organized as a small layered C++ application built with Raylib. The code is split by responsibility so that graph data, algorithms, and user-interface logic stay separated, while still remaining simple enough for a student project. The overall runtime flow is:

1. `main.cpp` creates an `App` object.
2. `App` initializes the window, fonts, `Graph`, `InputHandler`, and `Visualizer`.
3. `InputHandler` lets the user load or generate a graph and choose a TSP algorithm.
4. `Algorithms.cpp` runs the selected algorithm and produces a `TSPResult` with a step-by-step event history.
5. `Visualizer` replays those events, while `Graph` renders the graph and highlights the current path.

## Folder Structure

### `assets/`
This folder stores the fonts used by the interface. The application loads custom fonts here so the graph labels and side panel text have a consistent look.

### `include/`
This folder contains the public declarations of the project.

- `include/core/` contains the top-level application and graph declarations.
- `include/model/` contains lightweight data objects such as `Vertex` and `Edge`.
- `include/UI/` contains the input panel, playback visualizer, and side explanation panel.
- `include/Algorithms.h` contains the TSP algorithm interface and the visualization event types.

### `src/`
This folder contains the implementation files that match the headers in `include/`.

- `src/core/` implements the application loop and graph behavior.
- `src/model/` implements the simple data objects.
- `src/UI/` implements the user interface and playback controls.
- `src/Algorithms.cpp` implements the TSP algorithms.
- `src/main.cpp` is the entry point.


## Main Data Structures

### `Graph`
`Graph` is the central data structure of the project. It stores the vertices, edges, adjacency matrix, and the current TSP path. It also handles layout updates and rendering, so it acts as both the data model and the visual scene object.

The key internal containers are:

- `std::vector<Vertex> vertices` for node positions and animation state.
- `std::vector<Edge> edges` for directed weighted connections.
- `std::vector<std::vector<int>> adjacencyMatrix` for fast edge-weight lookup.
- `std::vector<int> currentTSPPath` for highlighting the final solution.

The adjacency matrix is a good choice here because the algorithms check edge existence and weight very often. A matrix gives constant-time lookup with `GetEdgeWeight(u, v)`, which is useful for backtracking and 2-opt. An adjacency list would save memory on sparse graphs, but it would make repeated weight checks less direct and would add more lookup logic in the algorithms and renderer.

### `Vertex` and `Edge`
`Vertex` and `Edge` are intentionally small data objects. They are kept minimal because `Graph` owns and manages them.

- `Vertex` stores the location, index, color, and velocity used by the force-directed layout.
- `Edge` stores the connected vertex indices, weight, and drawing color.

These could have been implemented as plain public structs, but the current class-based design keeps the fields private and lets `Graph` control all updates through `friend class Graph`. That is a reasonable choice for a compact visualization project because it avoids accidental state changes outside the graph system.

### `VisualizationEvent` and `TSPResult`
These two structures are the bridge between the algorithm layer and the visualization layer.

- `VisualizationEvent` stores a snapshot of one algorithm step: the current path, visited mask, current cost, best cost, best path, source-code line number, and description.
- `TSPResult` stores the final tour, total cost, and the full event timeline.

This event-based design is better than trying to animate the algorithm live inside the UI loop. By precomputing a list of events, the same algorithm output can support play, pause, next, previous, and speed control without rerunning the algorithm every frame.

### `App`, `InputHandler`, `Visualizer`, and `Sidepeak`
These classes organize the user experience.

- `App` owns the main loop and coordinates updates and drawing.
- `InputHandler` manages graph loading, random graph generation, dark mode, and algorithm selection.
- `Visualizer` manages playback of algorithm events.
- `Sidepeak` draws the explanation panel and highlights the pseudocode line associated with the current event.

## Implementation Details

### `App`
Relevant functions:

- `App::App(int width, int height, const char *title)` initializes the window, loads fonts, initializes the graph and visualizer, and creates a starting graph.
- `App::Run()` executes the main application loop.
- `App::Update()` updates the graph physics, input handling, visualization playback, and camera movement.
- `App::Draw()` renders the graph inside the camera and draws the UI outside the camera.

`App` is the central coordinator. It does not implement graph logic or TSP logic itself; instead, it keeps the frame loop organized and sends work to the specialized classes.

### `Graph`
Relevant functions:

- `Graph::Init(Font font)` stores the font used for labels.
- `Graph::LoadFromMatrix(const std::vector<std::vector<int>> &matrix)` rebuilds the graph from an adjacency matrix.
- `Graph::GenerteRandomMatrix(int numVertices)` creates a random weighted directed graph.
- `Graph::getMatrix(const std::string &filename)` loads a matrix from a file.
- `Graph::Update()` applies force-directed layout physics.
- `Graph::Draw(const VisualizationEvent *event, bool isDarkMode)` draws edges, weights, vertices, and visualization highlights.
- `Graph::SetTSPPath(const std::vector<int> &path)` stores the final tour for display.
- `Graph::GetEdgeWeight(int u, int v) const` returns the weight of a directed edge.
- `Graph::GetVertexCount() const` returns the number of vertices.

`Graph::Update()` and `Graph::Draw()` work together: the update step moves nodes into readable positions, and the draw step colors the current exploration path or final solution based on the active event.

### `InputHandler`
Relevant functions:

- `InputHandler::InputHandler(Graph &graphRef, Visualizer *vis)` stores references to the graph and visualizer.
- `InputHandler::Update()` manages warning timers.
- `InputHandler::Draw()` renders the GUI buttons and reacts to user actions.

`InputHandler` is the control panel for the application. It launches `TSP_BruteForce()` or `TSP_LocalSearch2Opt()`, sends the result to `Visualizer::SetResult()`, and updates the graph path with `Graph::SetTSPPath()`.

### `Visualizer`
Relevant functions:

- `Visualizer::Init(Font codeFont, Font descFont)` configures the side panel fonts.
- `Visualizer::SetResult(const TSPResult &res, const std::vector<std::string> &pseudoCode)` loads a new algorithm result.
- `Visualizer::Update()` advances the playback state when the animation is running.
- `Visualizer::DrawUI(int screenWidth, int screenHeight)` draws the playback controls and side panel.
- `Visualizer::GetCurrentEvent() const` returns the event currently being displayed.
- `Visualizer::IsActive() const` reports whether a result is loaded.
- `Visualizer::Stop()` clears playback.

`Visualizer` is the playback engine. It does not compute the algorithm; it only steps through the already computed event list and passes the current event to the UI and graph renderer.

### `Sidepeak`
Relevant functions:

- `Sidepeak::SetFont(Font codeF, Font descF)` stores the fonts used in the panel.
- `Sidepeak::SetCode(const std::vector<std::string> &code)` stores the pseudocode lines.
- `Sidepeak::Draw(...)` renders the description, best path text, and highlighted line.

`Sidepeak` is a focused view component. Keeping it separate from `Visualizer` makes the playback logic simpler and keeps text rendering isolated from control handling.

### `Algorithms`
Relevant functions:

- `TSP_BruteForce(const Graph &graph)` runs the exact backtracking solution.
- `TSP_LocalSearch2Opt(const Graph &graph)` runs the heuristic 2-opt solution.

The algorithms use `Graph::GetEdgeWeight()` and `Graph::GetVertexCount()` to inspect the graph without mutating it. They emit `VisualizationEvent` objects instead of drawing anything directly. That separation keeps the algorithms reusable and makes the visualization consistent across different approaches.

## Main Flows and How the Classes Collaborate

### 1. Graph initialization and loading

When the program starts, `App` initializes the window and fonts, then calls `Graph::GenerteRandomMatrix()` and `Graph::LoadFromMatrix()` to create a starting graph. Later, `InputHandler` can replace the graph by either generating a new random matrix or reading one from `matrix.txt` using `Graph::getMatrix()`.

In this flow, `InputHandler` decides what the user requested, `Graph` rebuilds its internal containers, and `App` keeps drawing the new state every frame.

### 2. Running Brute Force TSP

When the user presses the brute force button, `InputHandler` checks that the graph is small enough for an exact search. If it is, it calls `TSP_BruteForce(graph)`.

`TSP_BruteForce()` performs recursive backtracking. During recursion it records a `VisualizationEvent` whenever it visits a node, checks an edge, chooses an edge, backtracks, or finds a better tour. The final `TSPResult` is then passed to `Visualizer::SetResult()`.

After that, `Visualizer` replays the events one by one. `App::Draw()` forwards the current event to `Graph::Draw()`, which highlights the current path and visited vertices. The side panel shows the matching description and pseudocode line, so the user can see both the search process and the code logic at the same time.

### 3. Running 2-opt local search

When the user selects 2-opt, `InputHandler` calls `TSP_LocalSearch2Opt(graph)`. This algorithm builds an initial valid tour, then tries edge swaps to reduce the total cost.

The algorithm again records each important step as a `VisualizationEvent`: building the initial tour, scanning possible swaps, accepting an improvement, and stopping when no better swap exists. The resulting `TSPResult` is sent to the visualizer in the same way as brute force, which means both algorithms share the same playback pipeline.

This is a strong design choice because the UI does not need special-case logic for each algorithm. It only needs to display the current event data.

### 4. Rendering and interaction loop

Every frame, `App::Update()` updates graph physics, user input, and playback state. Then `App::Draw()` renders the graph with the current event, draws the side explanation panel, and overlays the GUI controls.

This separation of update and draw keeps the project readable. It also makes it easier to add future features such as dynamic speed control, more algorithms, or additional visualization panels.

## Summary of Design Choices

The project uses a matrix-based graph representation, a vector-based vertex/edge storage model, and an event timeline for algorithm playback. These choices favor simplicity, direct access, and easy visualization over maximum generality.

- The adjacency matrix is efficient for repeated edge lookup.
- `std::vector` keeps storage simple and iteration fast.
- `VisualizationEvent` makes algorithm playback reusable and deterministic.
- The split between `Graph`, `InputHandler`, `Visualizer`, and `Sidepeak` keeps the code modular.

Overall, the architecture is practical for a Raylib-based educational visualization tool: the data structures are small, the control flow is easy to follow, and the algorithms can be explained visually step by step.


## Technical Problems and Solutions
- The node placement -> Physic layout
- The edge weight being unreadable -> Give it offset
- The algorithm is running iffinitely -> Give limit to the brute force and give shortened algorithm to the Local search
- 