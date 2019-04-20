#pragma once

#include <float.h>
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <map>
#include "node.hpp"

class Graph
{
public:
  vector<Node *> nodes;

  Graph()
  {
    Node *eisenstadt = new Node("Eisenstadt", 10);
    Node *klagenfurt = new Node("Klagenfurt", 11);
    Node *sankt = new Node("Sankt Pölten", 5);
    Node *linz = new Node("Linz", 5);
    Node *salzburg = new Node("Salzburg", 4);
    Node *graz = new Node("Graz", 3);
    Node *innsbruck = new Node("Innsbruck", 3);
    Node *bregenz = new Node("Bregenz", 8);
    Node *wien = new Node("Wien", 1);

    nodes.push_back(eisenstadt);
    nodes.push_back(klagenfurt);
    nodes.push_back(sankt);
    nodes.push_back(linz);
    nodes.push_back(salzburg);
    nodes.push_back(graz);
    nodes.push_back(innsbruck);
    nodes.push_back(bregenz);
    nodes.push_back(wien);

    eisenstadt->addNeighbour(sankt, 67);
    eisenstadt->addNeighbour(graz, 106);
    eisenstadt->addNeighbour(wien, 47);

    klagenfurt->addNeighbour(graz, 193);
    klagenfurt->addNeighbour(innsbruck, 240);
    klagenfurt->addNeighbour(salzburg, 144);

    sankt->addNeighbour(wien, 61);
    sankt->addNeighbour(linz, 74);
    sankt->addNeighbour(graz, 161);
    sankt->addNeighbour(eisenstadt, 67);

    linz->addNeighbour(sankt, 74);
    linz->addNeighbour(graz, 147);
    linz->addNeighbour(salzburg, 77);

    salzburg->addNeighbour(linz, 77);
    salzburg->addNeighbour(graz, 180);
    salzburg->addNeighbour(klagenfurt, 144);
    salzburg->addNeighbour(innsbruck, 132);

    graz->addNeighbour(eisenstadt, 106);
    graz->addNeighbour(sankt, 161);
    graz->addNeighbour(linz, 147);
    graz->addNeighbour(salzburg, 180);
    graz->addNeighbour(klagenfurt, 144);

    innsbruck->addNeighbour(salzburg, 132);
    innsbruck->addNeighbour(bregenz, 130);

    bregenz->addNeighbour(innsbruck, 130);

    wien->addNeighbour(eisenstadt, 47);
    wien->addNeighbour(sankt, 61);
  };
  ~Graph(){};

  Node *getNode(string name)
  {
    for (auto node : nodes)
    {
      if (node->name == name)
      {
        return node;
      }
    }
    throw logic_error("Name " + name + " is invalid");
  }

  void getShortestPath(string start, string end)
  {
    auto startNode = getNode(start);
    auto endNode = getNode(end);

    vector<Node *> unvisited;
    vector<Node *> visited;
    for (auto node : nodes)
    {
      unvisited.push_back(node);
    }

    map<Node *, double> distances;
    for (auto node : nodes)
    {
      distances.insert_or_assign(node, DBL_MAX);
    }
    distances.insert_or_assign(startNode, startNode->handlingTime);

    auto current = startNode;
    while (true)
    {
      cout << "Current: " << current->name << endl;
      if (current == endNode)
      {
        break;
      }

      for (auto &pair : current->neightbours)
      {
        if (find(unvisited.begin(), unvisited.end(), current) == unvisited.end())
        {
          continue;
        }

        auto distance = distances[current] + pair.second + pair.first->handlingTime;
        if (distance < distances[pair.first])
        {
          distances[pair.first] = distance;
        }
      }

      visited.push_back(current);
      unvisited.erase(find(unvisited.begin(), unvisited.end(), current));

      double shortestDist = DBL_MAX;
      for (auto &node : unvisited)
      {
        auto distance = distances[node];
        if (distance < shortestDist)
        {
          shortestDist = distance;
          current = node;
        }
      }
    }
  }
};