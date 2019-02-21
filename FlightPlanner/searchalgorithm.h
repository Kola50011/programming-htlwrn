/*
 * Author: Lampalzer Konstantin
 * Class: 5BHIF
 * Date: 16.02.2019
 */

#ifndef SEARCHALGORITHM_H
#define SEARCHALGORITHM_H

#include <vector>
#include "dbmanager.h"

class SearchAlgorithm
{
  public:
    DbManager database = DbManager::getInstance();
    virtual std::vector<std::vector<int>> getRoutes(int start, int end) = 0;
};

#endif // SEARCHALGORITHM_H
