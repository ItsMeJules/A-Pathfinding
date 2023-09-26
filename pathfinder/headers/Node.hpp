#pragma once

#include <cmath>

struct Vec3i {
    int x;
    int y;
    int z;

    Vec3i() : x(-1), y(-1), z(-1) {}
    Vec3i(const Vec3i& other) : x(other.x), y(other.y), z(other.z) {}
    Vec3i(int x, int y, int z) : x(x), y(y), z(z) {}

    int distanceMul10(const Vec3i& other) {
        int xDistance = abs(x - other.x);
        int yDistance = abs(y - other.y);
        int zDistance = abs(z - other.z);

        int minimum = std::min(std::min(xDistance, yDistance), zDistance);
        int maximum = std::max(std::max(xDistance, yDistance), zDistance);
        
        int tripleAxis = minimum;
        int doubleAxis = xDistance + yDistance + zDistance - maximum - 2 * minimum;
        int singleAxis = maximum - doubleAxis - tripleAxis;

        int approximation = 10 * singleAxis + 14 * doubleAxis + 17 * tripleAxis;

        return approximation;
    }

    Vec3i operator=(const Vec3i& other) {
        x = other.x;
        y = other.y;
        z = other.z;

        return *this;
    }

    bool operator==(const Vec3i& other) const {
        return x == other.x && y == other.y && z == other.z;
    }
};

class Node {
    private:
        Vec3i _position;
        Node* _parent;
        int _g;
        int _h;
        bool _isWalkable;

    public:
        Node();
        Node(Vec3i position, bool isWalkable = true);
        Node(const Node& other);
        ~Node();

        Vec3i getPosition() const;
        Node* getParent() const;
        int getG() const;
        int getH() const;
        int getF() const;
        bool isWalkable() const;
        bool isMorePromisingThan(const Node& node) const;

        void setG(int g);
        void setH(int h);
        void setParent(Node* parent);

        Node& operator=(const Node& other);
        bool operator==(const Node& other) const;
};