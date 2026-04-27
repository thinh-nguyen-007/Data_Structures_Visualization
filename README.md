# Graph Visualizer + TSP Visualization

This project is a C++ + Raylib application for visualizing directed weighted graphs and the Traveling Salesperson Problem (TSP).

Current implemented algorithm:
- Brute Force TSP (with step-by-step visualization events)
- Local Search TSP (2-opt)

Planned/target algorithms:
- Dynamic Programming TSP
- Greedy TSP

## Project Structure and File Purpose

## Top-Level Files

- `CMakeLists.txt`
	- Build configuration for CMake.
	- Sets C++17, downloads Raylib via `FetchContent`, builds executable from `src/*.cpp`.

- `LICENSE`
	- Repository license text.

- `matrix.txt`
	- Sample adjacency matrix input file used by the app's "Load File" feature.

- `README.md`
	- This documentation file.

## assets/

- `assets/Agbalumo-Regular.ttf`
	- Main UI/code font loaded by the application (`App`) and used in graph labels.

- `assets/ChironGoRoundTC-VariableFont_wght (1).ttf`
	- Description font used for the Sidepeak tracking panel text.

## include/ and src/ 

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
		- Graph generation (2-7 nodes)
		- Matrix-file loading
		- Brute-force TSP run trigger
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

## Third party Header

- `include/raygui.h`
	- External immediate-mode GUI library header used for buttons, panel, textbox, slider, labels.

## Entry Point

- `src/main.cpp`
	- Program entry.
	- Creates `App` and starts `Run()` loop.

## build/ Folder

- `build/` and subfolders (`_deps`, `.vcxproj`, solution files, CMake cache, generated binaries)
	- Auto-generated build outputs from CMake/Visual Studio.
	- Not hand-edited source files.
	- Safe to recreate by re-configuring and rebuilding the project.

## Quick Logic Flow

1. `main.cpp` creates `App`.
2. `App` initializes window, fonts, graph, visualizer, and input handler.
3. Every frame:
	 - `Graph::Update()` animates node layout.
	 - `InputHandler::Draw()` reads user GUI actions.
	 - `Visualizer::Update()` advances playback timeline.
	 - `App::Draw()` renders graph and UI overlays.
4. On "Run Brute Force TSP":
	 - `TSP_BruteForce(graph)` computes result + events.
	 - `Visualizer` plays events step-by-step.
	 - `Graph` highlights current/final TSP path.