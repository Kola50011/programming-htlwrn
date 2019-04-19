#pragma once

#include <vector>
#include "node.hpp"

class Graph
{
  public:
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
};