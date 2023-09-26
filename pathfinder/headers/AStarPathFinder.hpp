#pragma once

#include <vector>
#include <algorithm>
#include <functional>

#include "Node.hpp"
#include "Maze.hpp"

namespace pf {
    std::vector<Vec3i*> findPath(const Maze& maze, const Vec3i& start, const Vec3i& end);
}