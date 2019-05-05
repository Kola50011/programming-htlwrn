#ifndef NODE_H
#define NODE_H

#include <vector>
#include <string>

class Node {
public:
    Node(std::string name, int value);
    std::vector<std::pair<Node*, int>> connected;
    void add_neighbour(Node* neighbour, int distance);
    std::string name;
    int value;
};

#endif // NODE_H
