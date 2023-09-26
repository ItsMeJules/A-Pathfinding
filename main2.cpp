#include <iostream>
#include <string>

#include "AStarPathFinder.hpp"
#include "Node.hpp"
#include "Maze.hpp"
#include "utils.hpp"

int main() {
    int mazeWidth = 3;
    int mazeHeight = 3;
    int mazeDepth = 3;

    Maze maze(mazeWidth, mazeHeight, mazeDepth);
    Vec3i start(0, 0, 0);
    Vec3i end(2, 2, 2);

    int tab[mazeWidth][mazeHeight][mazeDepth] = {
        {
            {0, 0, 0},
            {0, 1, 0},
            {0, 0, 0}
        },
        {
            {0, 0, 0},
            {0, 1, 0},
            {0, 0, 0}
        },
        {
            {0, 0, 0},
            {0, 1, 0},
            {0, 0, 0}
        }
    };

    for (int z = 0; z < maze.depth; z++) {  
        for (int y = 0; y < maze.height; y++) {
            for (int x = 0; x < maze.width; x++) {
                maze.map[z][y][x] = tab[z][y][x] == 1 ? '1' : '0';
            }
        }
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