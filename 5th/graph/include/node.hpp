#pragma once
#include <string>
#include <map>

using namespace std;

class Node
{
  public:
    string name;
    double handlingTime;
    map<Node *, double> neightbours;

    Node(string _name, double _handlingTime) : name{_name}, handlingTime{_handlingTime} {};
    ~Node() {};
    void addNeighbour(Node *neighbour, double time)
    {
        neightbours.insert_or_assign(neighbour, time);
    }
};