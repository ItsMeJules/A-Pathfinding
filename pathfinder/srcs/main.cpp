#include <iostream>
#include <string>

#include "AStarPathFinder.hpp"
#include "Node.hpp"
#include "Maze.hpp"
#include "utils.hpp"

int main(int ac, char **av) {
    if (ac != 2) {
        std::cerr << "Usage: ./pathfinder [maze file]" << std::endl;
        return 1;
    }

    Maze maze;
    Vec3i start;
    Vec3i end;

    if (!pf::parseMaze(av[1], maze, start, end)) {
        std::cerr << "Error: invalid maze file" << std::endl;
        pf::freeMaze(maze);
        return 1;
    }

    std::vector<Vec3i*> path = pf::findPath(maze, start, end);

    if (path.empty()) {
        std::cout << "No path found" << std::endl;
        pf::freeMaze(maze);
        return 0;
    }

    for (auto pos : path)
        std::cout << "(" << pos->x << ", " << pos->y << ", " << pos->z << ")" << std::endl;

    for (auto pos : path)
        delete pos;
    pf::freeMaze(maze);

    return 0;
}