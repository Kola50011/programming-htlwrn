#include "node.h"

Node::Node(std::string name, int value) {
    this->name = name;
    this->value = value;
}

void Node::add_neighbour(Node *neighbour, int distance) {
    this->connected.push_back(std::make_pair(neighbour, distance));
}
