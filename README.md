# Graph Visualizer + TSP Visualization

This project is a C++ + Raylib application for visualizing directed weighted graphs and Traveling Salesperson Problem (TSP) algorithms.

Implemented algorithms:
- Brute Force TSP (backtracking + visualization events)
- Local Search TSP (2-opt + visualization events)

## Filesystem Guide

This repository is organized by responsibility so readers can find code quickly.

```text
CS163 Final Project/
├─ assets/
│  ├─ Agbalumo-Regular.ttf
│  └─ ChironGoRoundTC-VariableFont_wght.ttf
├─ include/
│  ├─ core/
│  │  ├─ App.h
│  │  └─ Graph.h
│  ├─ model/
│  │  ├─ Edge.h
│  │  └─ Vertex.h
│  ├─ UI/
│  │  ├─ InputHandler.h
│  │  ├─ Sidepeak.h
│  │  └─ Visualizer.h
│  ├─ Algorithms.h
│  └─ raygui.h
├─ src/
│  ├─ core/
│  │  ├─ App.cpp
│  │  └─ Graph.cpp
│  ├─ model/
│  │  ├─ Edge.cpp
│  │  └─ Vertex.cpp
│  ├─ UI/
│  │  ├─ InputHandler.cpp
│  │  ├─ Sidepeak.cpp
│  │  └─ Visualizer.cpp
│  ├─ Algorithms.cpp
│  └─ main.cpp
├─ CMakeLists.txt
├─ matrix.txt
├─ README.md
└─ LICENSE
```

## Folder Purpose

### assets/
- Stores fonts used by the UI.
- `Agbalumo-Regular.ttf`: main app font for labels and main text.
- `ChironGoRoundTC-VariableFont_wght (1).ttf`: side panel description font.

### include/
- Public declarations (interfaces, structs, class definitions).
- Split by feature area:
  - `core/`: high-level app and graph system declarations.
  - `model/`: lightweight data objects (`Edge`, `Vertex`).
  - `UI/`: user interaction and visualization panels.
  - `Algorithms.h`: algorithm contracts and event/result structs.

### src/
- Implementations for headers in `include/`.
- Mirrors the same split (`core`, `model`, `UI`) so each header has a natural implementation location.
- `main.cpp` is program entry.
- `Algorithms.cpp` contains TSP algorithm implementations.

## File-by-File Purpose

### Core
- `include/core/App.h` + `src/core/App.cpp`
  - Creates window, initializes systems, runs the main update/draw loop, handles camera behavior.

- `include/core/Graph.h` + `src/core/Graph.cpp`
  - Graph storage, matrix loading/random generation, force-directed layout, graph rendering, and TSP path highlighting.

### Models
- `include/model/Vertex.h` + `src/model/Vertex.cpp`
  - Vertex data (position, velocity, index, style fields).

- `include/model/Edge.h` + `src/model/Edge.cpp`
  - Edge data (directed endpoints, weight, style fields).

### UI
- `include/UI/InputHandler.h` + `src/UI/InputHandler.cpp`
  - GUI controls for graph loading/generation, algorithm execution, dark mode, and warning messages.

- `include/UI/Visualizer.h` + `src/UI/Visualizer.cpp`
  - Playback engine for algorithm events (play/pause/prev/next/speed/stop).

- `include/UI/Sidepeak.h` + `src/UI/Sidepeak.cpp`
  - Side panel that displays step descriptions, best path, and highlighted pseudocode lines.

### Algorithms
- `include/Algorithms.h` + `src/Algorithms.cpp`
  - Algorithm input/output contracts (`VisualizationEvent`, `TSPResult`) and TSP implementations:
    - `TSP_BruteForce`
    - `TSP_LocalSearch2Opt`

### Entry and Build
- `src/main.cpp`
  - Entry point. Creates `App` and starts `Run()`.

- `CMakeLists.txt`
  - Build script. Sets C++ standard, fetches raylib, and builds all `src/*.cpp` files.

- `matrix.txt`
  - Example matrix input for file-based graph loading.

## How Data Flows Across Folders
1. `main.cpp` starts `App` (`core`).
2. `App` updates `Graph` (`core`), `InputHandler` (`UI`), and `Visualizer` (`UI`) every frame.
3. `InputHandler` launches algorithms from `Algorithms.cpp`.
4. Algorithms return `TSPResult` + event timeline.
5. `Visualizer` replays events and `Graph` highlights current/final paths.
6. `Sidepeak` shows explanation text and pseudocode highlight for each event.

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
| **Graph Size**               |    2-7      |      2 - 50          |