#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <string>
#include <node.h>
#include <unordered_map>
#include <queue>
#include <algorithm>
#include <iostream>

#include <QtDebug>
#include <QDebug>
#include <QString>

class Graph {
public:
    Graph();
    std::vector<Node*> get_route(std::string from, std::string to);
    std::vector<std::vector<Node*>> get_route_breadth_first_search(std::string from, std::string end);
private:
    std::vector<std::vector<Node*>> backtracking(std::unordered_map<Node*, std::vector<Node*>>& predecessors, Node* start_node, Node* destination);
    std::vector<Node*> nodes;
    Node *get_node_from_name(std::string name);
};

#endif // GRAPH_H
