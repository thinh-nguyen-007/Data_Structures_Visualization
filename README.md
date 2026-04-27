# Graph Visualizer + TSP Visualization
This project is a C++ + Raylib application for visualizing directed weighted graphs and the Traveling Salesperson Problem (TSP).

## Algorithms Overview
Current implemented algorithms:
- Brute Force TSP (with step-by-step visualization events)
- Local Search TSP (2-opt)

### 1. Brute Force TSP (Backtracking)
**File:** `src/Algorithms.cpp` - `TSP_BruteForce()` function

**How it works:**
- Uses recursive backtracking to explore all possible Hamiltonian cycles starting from vertex 0.
- At each step, tries to extend the current path by visiting each unvisited neighbor.
- Maintains the best (minimum cost) complete tour found so far.
- When all vertices are visited, checks if there's an edge back to start vertex.
- Records visualization events at every major decision:
  - Visiting a node
  - Checking an edge
  - Choosing an edge
  - Backtracking from a branch

**Characteristics:**
- **Time Complexity:** O(n!) in worst case (explores all permutations)
- **Space Complexity:** O(n) for recursion stack
- **Optimality:**  Guarantees the globally optimal solution
- **Use Case:** Small graphs (2-7 nodes recommended). Perfect for learning and understanding backtracking.
- **Visualization:** Shows exact search tree traversal with every branch and backtrack.

---
### 2. Local Search TSP (2-opt Heuristic) 
**File:** `src/Algorithms.cpp` - `TSP_LocalSearch2Opt()` function

**How it works:**
- Starts with an initial valid tour (random incremental build, with nearest-neighbor fallback).
- Repeatedly removes two edges from the tour and reconnects the path in a different way.
- A **2-opt swap** reverses a segment of the tour to potentially reduce total distance.
- Continues until no improvement can be made (local optimum reached).

**Characteristics:**
- **Time Complexity:** O(n²) swap checks per pass (repeated until no improvement)
- **Space Complexity:** O(n)
- **Optimality:**  Does NOT guarantee global optimum (finds local optimum)
- **Use Case:** Medium to large graphs. Fast approximation when exact solutions are impractical.
- **Visualization:** Shows incremental tour improvements with each 2-opt swap highlighted.


### Algorithm Comparison Table

|           Feature            | Brute Force | Local Search (2-opt) |
|------------------------------|-------------|----------------------|
| **Optimal Solution**         |   Yes       |   No (local optimum) |
| **Speed**                    |  Slow (n!)  |   Fast (heuristic)   |
| **Graph Size (this app)**    | 2-7 recommended | 2-50 supported   |

## Project Structure and File Purpose

### Top-Level Files

- `CMakeLists.txt`
	- Build configuration for CMake.
	- Sets C++17, downloads Raylib via `FetchContent`, builds executable from `src/*.cpp`.

- `LICENSE`
	- Repository license text.

- `matrix.txt`
	- Sample adjacency matrix input file used by the app's "Load File" feature.

- `README.md`
	- This documentation file.

### assets/

- `assets/Agbalumo-Regular.ttf`
	-UI/code font loaded by the application (`App`) and used in graph labels.

- `assets/ChironGoRoundTC-VariableFont_wght (1).ttf`
	- Description font used for the Sidepeak tracking panel text.

### include/ and src/ 

For each module below, `.h` defines interfaces/data types and `.cpp` implements behavior.

- `include/App.h` + `src/App.cpp`
	- Main application coordinator.
	- Owns `Graph`, `Visualizer`, `InputHandler`, camera, and fonts.
	- Initializes window/resources and runs the frame loop (`Update` + `Draw`).
	- Handles camera pan/zoom and global rendering order.

- `include/Graph.h` + `src/Graph.cpp`
	- Core graph model + renderer + auto-layout simulation.
	- Stores vertices, edges, adjacency matrix, and current highlighted TSP path.
	- Loads graph from matrix/random generator.
	- Draws nodes, directed edges, weights, and event-based highlights.
	- Updates vertex positions using force-based layout (repulsion/attraction/gravity/damping).

- `include/Algorithms.h` + `src/Algorithms.cpp`
	- TSP algorithm contract and brute-force implementation.
	- Defines:
		- `VisualizationEvent`: one snapshot step for playback/highlighting.
		- `TSPResult`: final path/cost plus all events.
	- Implements recursive backtracking brute-force TSP and emits events at key decision points.

- `include/Visualizer.h` + `src/Visualizer.cpp`
	- Event playback controller.
	- Receives `TSPResult`, stores timeline, controls step index, play/pause, and speed.
	- Exposes current event for graph highlighting.
	- Draws playback controls (`Play`, `Prev`, `Next`, speed slider, `Stop`).

- `include/InputHandler.h` + `src/InputHandler.cpp`
	- UI interaction layer (raygui).
	- Handles:
		- Graph generation (2-50 nodes)
		- Matrix-file loading
		- Brute-force TSP run trigger
		- Local-search (2-opt) run trigger
		- Dark mode toggle
	- Sends algorithm result to `Visualizer` and final path to `Graph`.

- `include/Sidepeak.h` + `src/Sidepeak.cpp`
	- Side panel renderer for visualization guidance.
	- Displays event description, best path/cost, pseudocode, and active highlighted line.

- `include/Vertex.h` + `src/Vertex.cpp`
	- Vertex data model.
	- Stores node position, index, display color, and simulation velocity.

- `include/Edge.h` + `src/Edge.cpp`
	- Edge data model.
	- Stores directed connection `(u, v)`, edge weight, and edge color.

### Third party Header

- `include/raygui.h`
	- External immediate-mode GUI library header used for buttons, panel, textbox, slider, labels.

### Entry Point

- `src/main.cpp`
	- Program entry.
	- Creates `App` and starts `Run()` loop.


## Quick Logic Flow

1. `main.cpp` creates `App`.
2. `App` initializes window, fonts, graph, visualizer, and input handler.
3. Every frame has two phases:
	- **Update phase** (`App::Update`):
		- `Graph::Update()` animates node layout.
		- `InputHandler::Update()` handles UI timers (e.g., brute-force size warning).
		- `Visualizer::Update()` advances playback timeline.
	- **Draw phase** (`App::Draw`):
		- Graph is drawn (with event highlighting if visualizer is active).
		- `Visualizer::DrawUI()` draws side panel and playback controls.
		- `InputHandler::Draw()` renders and processes GUI buttons.
4. On "Run Brute Force TSP":
	- If graph size is greater than 7, show a warning and skip execution.
	- Otherwise call `TSP_BruteForce(graph)` to generate result + events.
	- Pass events to `Visualizer` for step-by-step playback.
	- Pass final best path to `Graph` for path highlighting.
5. On "Run 2-opt TSP":
	- Call `TSP_LocalSearch2Opt(graph)` to generate an initial valid tour and improve it with 2-opt swaps.
	- Pass events to `Visualizer` for step-by-step playback.
	- Pass final best path to `Graph` for path highlighting.