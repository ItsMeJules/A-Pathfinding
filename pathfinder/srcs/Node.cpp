#include "Node.hpp"

Node::Node() :
    _position(Vec3i()), _parent(nullptr), _g(0), _h(0), _isWalkable(true) {}

Node::Node(Vec3i position, bool isWalkable) :
    _position(position), _parent(nullptr), _g(0), _h(0), _isWalkable(isWalkable) {}

Node::Node(const Node& other) {
    *this = other;
}

Node::~Node() {}

Vec3i Node::getPosition() const {
    return _position;
}

Node* Node::getParent() const {
    return _parent;
}

int Node::getG() const {
    return _g;
}

int Node::getH() const {
    return _h;
}

int Node::getF() const {
    return _g + _h;
}

bool Node::isWalkable() const {
    return _isWalkable;
}

bool Node::isMorePromisingThan(const Node& node) const {
    int currentF = getF();
    int nodeF = node.getF();
    return currentF < nodeF || (currentF == nodeF && _h < node._h);
}

void Node::setG(int g) {
    _g = g;
}

void Node::setH(int h) {
    _h = h;
}

void Node::setParent(Node* parent) {
    _parent = parent;
}

Node& Node::operator=(const Node& other) {
    _position = other._position;
    _parent = other._parent;
    _g = other._g;
    _h = other._h;
    _isWalkable = other._isWalkable;

    return *this;
}

bool Node::operator==(const Node& other) const {
    return _position == other._position;
}   