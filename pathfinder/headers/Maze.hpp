#pragma once

struct Maze {
    int width;
    int height;
    int depth;
    char ***map;

    Maze() : width(0), height(0), depth(0), map(nullptr) {}
    Maze(int width, int height, int depth) : width(width), height(height), depth(depth) {
        map = new char**[depth];
        for (int z = 0; z < depth; z++) {
            map[z] = new char*[height];
            for (int y = 0; y < height; y++) {
                map[z][y] = new char[width];
            }
        }
    }
};