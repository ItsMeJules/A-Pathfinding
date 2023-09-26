#include "AStarPathFinder.hpp"
#include <ostream>

namespace pf {

    int approximateDiscoveredCells(const Vec3i& start, const Vec3i& end) {
        int xDistance = abs(start.x - end.x) + 1;
        int yDistance = abs(start.y - end.y) + 1;
        int zDistance = abs(start.z - end.z) + 1;

        return xDistance * yDistance * zDistance;
    }

    std::vector<Vec3i*> reconstructPath(Node* node) {
        std::vector<Vec3i*> path;
        Node* currentNode = node;

        while (currentNode != nullptr) {
            path.push_back(new Vec3i(currentNode->getPosition()));
            currentNode = currentNode->getParent();
        }

        std::reverse(path.begin(), path.end());
        return path;
    }

    void clearNodes(std::vector<Node*>& nodes) {
        for (auto node : nodes)
            delete node;
    }

    void clean(std::vector<Node*> v1, std::vector<Node*> v2, Node* n) {
        delete n;
        clearNodes(v1);
        clearNodes(v2);
    }

    std::vector<Node> getNeighbours(const Maze& maze, const Vec3i& pos) {
        std::vector<Node> neighbours;

        for (int z = -1; z <= 1; z++) {
            for (int y = -1; y <= 1; y++) {
                for (int x = -1; x <= 1; x++) {
                    if (x == 0 && y == 0 && z == 0)
                        continue;

                    Vec3i neighbour(pos.x + x, pos.y + y, pos.z + z);

                    if (neighbour.x >= 0 && neighbour.x < maze.width &&
                        neighbour.y >= 0 && neighbour.y < maze.height &&
                        neighbour.z >= 0 && neighbour.z < maze.depth &&
                        maze.map[neighbour.z][neighbour.y][neighbour.x] == '0') {
                        neighbours.push_back(Node(neighbour));
                    }
                }
            }
        }

        return neighbours;
    }

    bool isInList(const Node& node, const std::vector<Node*>& nodeList) {
        return std::find_if(nodeList.begin(), nodeList.end(),
            [node](const Node* n) {
                if (n == nullptr)
                    return false;
                return *n == node;
            }) != nodeList.end();
    }

    std::vector<Vec3i*> findPath(const Maze& maze, const Vec3i& start, const Vec3i& end) {
        Node *startNode = new Node(start);
        Node *endNode = new Node(end);
        Node *currentNode = nullptr;

        int possibleNodesAmount = approximateDiscoveredCells(start, end);
        std::vector<Node*> nodesToCheck;
        std::vector<Node*> checkedNodes;

        checkedNodes.reserve(possibleNodesAmount);
        nodesToCheck.reserve(possibleNodesAmount);
        nodesToCheck.push_back(startNode);

        while (!nodesToCheck.empty()) {
            auto current_it = std::min_element(nodesToCheck.begin(), nodesToCheck.end(),
                [](const Node* a, const Node* b) {
                    return a->isMorePromisingThan(*b);
                });
            currentNode = *current_it;

            if (*currentNode == *endNode) {
                std::vector<Vec3i*> path = reconstructPath(currentNode);
                clean(nodesToCheck, checkedNodes, endNode);
                return path;
            }

            checkedNodes.push_back(currentNode);
            nodesToCheck.erase(current_it);

            for (Node& neighbour : getNeighbours(maze, currentNode->getPosition())) {
                if (isInList(neighbour, checkedNodes))
                    continue;

                int g = currentNode->getG() + currentNode->getPosition().distanceMul10(neighbour.getPosition());
                if (!isInList(neighbour, nodesToCheck)) {
                    neighbour.setParent(currentNode);
                    neighbour.setG(g);
                    neighbour.setH(neighbour.getPosition().distanceMul10(endNode->getPosition()));
                    nodesToCheck.push_back(new Node(neighbour));
                } else if (g < currentNode->getG()) {
                    neighbour.setParent(currentNode);
                    neighbour.setG(g);
                }
            }
        }
        clean(nodesToCheck, checkedNodes, endNode);
        return std::vector<Vec3i*>();
    }
}