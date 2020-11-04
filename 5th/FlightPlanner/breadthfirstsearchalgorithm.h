/*
 * Author: Lampalzer Konstantin
 * Class: 5BHIF
 * Date: 16.02.2019
 */

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
        // Possible solution:
        // Find shortest amount of hops
        // Do BFS till depth = min - 1
        //  Keep Track of the predecessors of all neighbours
        // Take pred. of end node and backtrack all routes recursively
        //  AKA. recusively go into all pred. .
        // This works, as pred. have to have some route to the start node

        std::vector<std::vector<int>> routes;
        int depth = getShortestDepth(start, end);

        auto predecessors = generatePredecessors(start, depth);
        routes = backtrack({end}, depth, end, start, predecessors);

        for (auto &route : routes)
        {
            std::reverse(route.begin(), route.end());
        }

        return routes;
    }

  private:
    std::vector<std::vector<int>> backtrack(std::vector<int> prev, int depth, int start, int end, std::map<int, std::vector<int>> &predecessors)
    {
        std::vector<std::vector<int>> ret;

        if (depth == 0)
        {
            if (start == end)
            {
                std::vector<int> newPrev = prev;
                //newPrev.push_back(end);
                ret.push_back(newPrev);
            }
        }
        else
        {
            auto nbs = predecessors[start];
            for (auto &airport : nbs)
            {
                if (std::find(prev.begin(), prev.end(), airport) != prev.end())
                {
                    continue;
                }

                std::vector<int> newPrev = prev;
                newPrev.push_back(airport);

                auto toConcat = backtrack(newPrev, depth - 1, airport, end, predecessors);
                if (toConcat.size() != 0)
                {
                    ret.insert(ret.end(), toConcat.begin(), toConcat.end());
                }
            }
        }
        return ret;
    }

    std::map<int, std::vector<int>> generatePredecessors(int start, int goalDepth)
    {
        int depth{0};
        std::map<int, std::vector<int>> result;
        std::queue<int> currentLayer;
        std::queue<int> nextLayer;
        std::map<int, bool> visited;

        currentLayer.push(start);
        int next = start;

        while (depth != goalDepth)
        {
            if (!visited[next])
            {
                visited[next] = true;
                for (auto &airport : database.getNeighbours(next))
                {
                    if (visited[airport] != true)
                    {
                        nextLayer.push(airport);
                        result[airport].push_back(next);
                    }
                }
            }

            currentLayer.pop();
            if (currentLayer.empty())
            {
                depth += 1;
                currentLayer = nextLayer;
                if (currentLayer.empty())
                {
                    return result;
                }
            }
            next = currentLayer.front();
        }

        return result;
    }

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
