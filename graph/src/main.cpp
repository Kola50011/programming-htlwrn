// http://www.engr.mun.ca/~theo/Misc/exp_parsing.htm
#include <string>
#include <iostream>
#include <vector>
#include <regex>
#include <stack>

#include "expressions.hpp"
#include "parser.hpp"

using namespace std;

int main(int argc, const char *argv[])
{
    if (argc != 2)
    {
        cout << "Please provide exactly 1 argument with the mathematical expression!" << endl;
        return 1;
    }
    return 0;
}
