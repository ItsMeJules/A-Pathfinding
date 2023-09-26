#pragma once

#include <iostream>
#include <limits>
#include <algorithm>
#include <fstream>
#include <vector>
#include <string.h>

#include "Node.hpp"
#include "Maze.hpp"

namespace pf {
    bool parseMaze(const char* mazeFile, Maze& maze, Vec3i& start, Vec3i& end);
    void freeMaze(Maze& maze);
    void printMap(const Maze& maze, const Vec3i& start, const Vec3i& end, std::vector<Vec3i*>& path);
}