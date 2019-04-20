// http://www.engr.mun.ca/~theo/Misc/exp_parsing.htm
#include <string>
#include <iostream>
#include <vector>
#include <regex>
#include <stack>

#include "graph.hpp"

using namespace std;

int main(int argc, const char *argv[])
{
    if (argc != 3)
    {
        cout << "Please provide exactly 2 arguments with the start and end node!" << endl;
        return 1;
    }

    Graph graph{};
    graph.getShortestPath(argv[1], argv[2]);
    return 0;
}
