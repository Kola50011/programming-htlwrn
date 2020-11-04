/*
 * Author: Lampalzer Konstantin
 * Class: 5BHIF
 * Date: 16.02.2019
 */

#ifndef CUSTOMSEARCHALGORITHM_H
#define CUSTOMSEARCHALGORITHM_H

#include "searchalgorithm.h"
#include <future>

class CustomSearchAlgorithm : public SearchAlgorithm
{
  public:
    CustomSearchAlgorithm(){};

    std::vector<std::vector<int>> getRoutes(int start, int end)
    {
        std::vector<std::vector<int>> routes;
        int depth{0};
        do
        {
            routes = getRoutesInternal({start}, depth, start, end);
            qDebug() << depth;
            depth += 1;
        } while (routes.size() == 0 && depth <= 4);
        return routes;
    }

  private:
    std::vector<std::vector<int>> getRoutesInternal(std::vector<int> prev, int depth, int start, int end)
    {
        std::vector<std::vector<int>> ret;

        if (depth == 0)
        {
            if (database.isConnected(start, end))
            {
                std::vector<int> newPrev = prev;
                newPrev.push_back(end);
                ret.push_back(newPrev);
            }
        }
        else
        {
            auto nbs = database.getNeighbours(start);
            std::vector<std::future<std::vector<std::vector<int>>>> futs;

            for (auto &airport : nbs)
            {
                if (std::find(prev.begin(), prev.end(), airport) != prev.end())
                {
                    continue;
                }

                std::vector<int> newPrev = prev;
                newPrev.push_back(airport);

                if (depth == 4)
                {
                    futs.push_back(std::async(&CustomSearchAlgorithm::getRoutesInternal, this, newPrev, depth - 1, airport, end));
                }
                else
                {
                    auto toConcat = getRoutesInternal(newPrev, depth - 1, airport, end);
                    if (toConcat.size() != 0)
                    {
                        ret.insert(ret.end(), toConcat.begin(), toConcat.end());
                    }
                }
            }

            for (auto &fut : futs)
            {
                auto toConcat = fut.get();
                ret.insert(ret.end(), toConcat.begin(), toConcat.end());
            }
        }
        return ret;
    }
};

#endif // CUSTOMSEARCHALGORITHM_H
