#ifndef BREADTHFIRSTSEARCHALGORITHM_H
#define BREADTHFIRSTSEARCHALGORITHM_H

#include "searchalgorithm.h"
#include "queue"
#include "map"

class BreadthFirstSearchAlgorithm : public SearchAlgorithm
{
public:
    BreadthFirstSearchAlgorithm() {}
    std::vector<std::vector<int>> getRoutes(int start, int end)
    {
        // TODO
        // Possible solution:
        // Find shortest amount of hops
        // Do BFS till depth = min - 1
        //  Keep Track of the predecessors of all neighbours
        // Take pred. of end node and backtrack all routes recursively
        //  AKA. recusively go into all pred. . This works, as pred. have to have some route to the start node

        std::vector<std::vector<int>> routes;
        int depth = getShortestDepth(start, end);
        qDebug() << depth;
        return routes;
    }

private:
    int getShortestDepth(int start, int end)
    {
        int depth{0};
        std::queue<int> currentLayer;
        std::queue<int> nextLayer;
        std::map<int, bool> visited;

        currentLayer.push(start);
        visited[start] = true;
        int next = start;
        while (next != end)
        {
            for (auto &airport : database.getNeighbours(next))
            {
                if (visited[airport] != true)
                {
                    visited[airport] = true;
                    nextLayer.push(airport);
                }
            }

            currentLayer.pop();
            if (currentLayer.empty())
            {
                depth += 1;
                currentLayer = nextLayer;
                if (currentLayer.empty())
                {
                    return -1;
                }
            }
            next = currentLayer.front();
        }
        return depth;
    }
};

#endif // BREADTHFIRSTSEARCHALGORITHM_H
