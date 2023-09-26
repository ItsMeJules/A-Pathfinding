#include "utils.hpp"

namespace pf {
    bool parseMaze(const char* mazeFile, Maze& maze, Vec3i& start, Vec3i& end) {
        std::ifstream file(mazeFile);

        if (!file.is_open()) {
            std::cerr << "Error: Unable to open maze file." << std::endl;
            return false;
        }

        char comma;
        file >> maze.width >> comma >> maze.height >> comma >> maze.depth;
        file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        file >> start.x >> comma >> start.y >> comma >> start.z;
        file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        file >> end.x >> comma >> end.y >> comma >> end.z;
        file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        int z = 0;
        int y = 0;

        maze.map = new char**[maze.depth];
        maze.map[z] = new char*[maze.height];

        std::string line;
        while (std::getline(file, line)) {
            if (line.empty() || line == "\r") {
                if (z >= maze.depth - 1) {
                    break;
                }
                z++;
                y = 0;
                maze.map[z] = new char*[maze.height];
                continue;
            }

            maze.map[z][y] = new char[maze.width];
            for (int x = 0; x < maze.width; x++) {
                maze.map[z][y][x] = line[x];
            }
            y++;
        }

        return true;
    }

    void freeMaze(Maze& maze) {
        for (int i = 0; i < maze.depth; i++) {
            for (int j = 0; j < maze.height; j++) {
                delete[] maze.map[i][j];
            }
            delete[] maze.map[i];
        }
        delete[] maze.map;
    }

    void printMap(const Maze& maze, const Vec3i& start, const Vec3i& end, std::vector<Vec3i*>& path) {
        for (int i = 0; i < maze.depth; i++) {
            for (int j = 0; j < maze.height; j++) {
                for (int k = 0; k < maze.width; k++) {
                    if (i == start.z && j == start.y && k == start.x)
                        std::cout << 'S';
                    else if (i == end.z && j == end.y && k == end.x)
                        std::cout << 'E';
                    else if (maze.map[i][j][k] == '1')
                        std::cout << 'x';
                    else if (std::find_if(path.begin(), path.end(), [&k, &j, &i](Vec3i const *v) {
                                return v->x == k && v->y == j && v->z == i;
                            }) != path.end())
                        std::cout << 'o';
                    else if (maze.map[i][j][k] == '0')
                        std::cout << '.';
                    else
                        std::cout << maze.map[i][j][k];
                }
                std::cout << std::endl;
            }
            std::cout << std::endl;
        }
    }
}