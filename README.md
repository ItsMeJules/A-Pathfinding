# 3D Maze Solver

**Overview**

This repository contains a 3D maze solving program implemented in C++. It generates a 3D maze, performs pathfinding using the A* algorithm, and provides you with the list of cells needed to navigate from the start to the end point in the maze.

**Getting Started**

To run the program with the provided 3D maze generator:

1. Navigate to the "maze_generator" directory:
    ```
    cd maze_generator
    ```

2. Generate a maze by executing the following command, where `<width>`, `<height>`, and `<depth>` are the dimensions of your maze:
    ```
    python3 maze_generator.py <width> <height> <depth>
    ```

3. Now, navigate to the "pathfinder" directory:
    ```
    cd ../pathfinder
    ```

4. Build the C++ program using the Makefile:
    ```
    make
    ```

5. Run the program with the generated maze file:
    ```
    ./maze ../maze_generator/<generated_file>
    ```

6. The program will calculate and display the list of cells required to reach the end point in the console.

If you want to use your own maze or implementation, follow these steps:

1. Move `main.cpp` out of the "pathfinder" folder.

2. Move `main2.cpp` into the "pathfinder" folder.

3. Edit the variables in the `main` function in `main2.cpp` as needed for your custom implementation.

4. Build the C++ program again:
    ```
    make re
    ```

5. Run the program with your custom configuration:
    ```
    ./maze
    ```

**Project Timeline**

Here's a breakdown of the time spent on this project:

- Research work: Approximately 20 minutes.
- Understanding the problem and A* algorithm: Around 1 hour.
- Code architecture design: Roughly 10 minutes.
- Pathfinding implementation: About 2 hours.
- Debugging: Approximately 1 hour and 30 minutes.
- Maze generation and parsing: Around 1 hour and 30 minutes.

Total time spent on this project: Approximately 7 hours.

**Code Structure**

The code is structured as follows:

- `Maze` class: Responsible for storing the maze and associated metadata.
- `Vec3i` struct: Represents a 3D integer point, used to compute distances without floating-point numbers.
- `Node` class: Represents a node with A* algorithm-related data (gCost, hCost, isWall).
- `AStarPathFinder` class: Contains the main pathfinding function and some private functions.
- `utils` class: A utility class responsible for memory management, maze parsing, and printing.

**Optimizations**

Here are some potential optimizations for your project:

1. Implement a Binary Tree to store nodes instead of a vector for `nodesToCheck` to improve the efficiency of finding the lowest `fCost` (AStarPathFinder:66).

2. Consider interpolating the 3D array into a 1D array to make memory contiguous and access faster.

3. Explore the possibility of using threads for parallel processing, although this may be overkill...
