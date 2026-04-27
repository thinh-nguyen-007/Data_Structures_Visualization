# Data_Structures_Visualization: Singly Linked-List
## NAME: NGUYEN XUAN GIA KHANG
## STUDENT ID: 25125073
## CLASS: 25A02
## Introduction

An interactive application designed to visualize Linked List data structures, built using CMake tool and SFML 3.0.2. This project provides a visual representation of data operations (Insert, Delete, Search) through real-time animations.

---

### Project Structure

The source code is organized into a modular architecture to separate logic from presentation:

#### 1. LinkedList (Core Logic)
Contains the fundamental logic of the data structure.
* **include/LinkedList.hpp**: Defines the Node structure and the LinkedList class. Declares core methods such as insert, remove, and search.
* **src/LinkedList.cpp**: Implements the technical algorithms for list manipulation, including pointer management and memory allocation.

#### 2. LinkedListCommand (Command Pattern)
Encapsulates list operations into command objects.
* **LinkedListCommand.hpp / .cpp**: Manages the execution flow. This allows for controlled simulation steps and potentially supports features like Undo/Redo.

#### 3. Visualization (Graphics & UI)
Responsible for rendering and user interaction.
* **main.cpp**: The entry point of the application. It contains the main game loop and initializes the Raylib window.
* **Animation.hpp / .cpp**: Handles movement logic. It calculates the interpolation of elements over time to create smooth transitions.
* **LinkedListRenderer.hpp / .cpp**: Specifically handles drawing the Nodes, pointers (arrows), and data values to the screen.
* **UI.hpp / .cpp**: Manages user interface elements such as buttons, input boxes, and navigation menus.
* **Design.hpp**: Centralizes design constants including color palettes, Node dimensions, spacing, and font settings.
* **data.txt**: A configuration file used to pre-load list data during startup.

#### 4. Build System & Resources
* **CMakeLists.txt**: Configuration files for the CMake build system to link dependencies and compile the project.
* **assets/**: Directory for external resources such as images, fonts, or icons.

---

### Key Features

- **Data Operations**: Supports Adding (Head/Tail/Middle), Removing, Searching, and Updating elements.
- **Visual Animation**: Displays the traversal process and the dynamic linking of Nodes during modifications.
- **Interactive Interface**: Allows users to input values via the keyboard and adjust simulation speeds.
- **File Initialization**: Automatically builds the initial list state from the provided data.txt file.

---

### Build Instructions

#### Prerequisites
* **C++ Compiler**: Support for C++17 or higher.
* **CMake**: Version 3.24 or higher.
* **SFML 3.0.2**: Must be installed and discoverable by CMake.

#### Building and Running the Project
Follow these steps to compile and run the application from the terminal:

```bash
# 1. Navigate to the project folder and generate
cd "project location"
cmake -S . -B build

# 2. Build
cmake --build build --config Debug

# 3. Copy and paste the assets and arial.ttf file in Visualization folder in build folder

# 4. Run the application (Choose the command based on your OS)
# For Windows:
cd build/Visualization/Debug
./Visualization.exe
# For Linux/macOS:
./Visualization/Visualization