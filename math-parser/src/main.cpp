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

    string input = argv[1];
    std::regex token_re{"\\+|-|\\(|\\)|/|\\*"};
    std::regex whitespace{" +"};
    input = std::regex_replace(input, whitespace, "");
    input = std::regex_replace(input, token_re, " $& ");
    cout << "Input: " << input << endl;

    // Tokenize
    istringstream inputStream{input};
    string token;
    vector<string> tokens;
    while (getline(inputStream, token, ' '))
    {
        if (token != string{" "})
        {
            tokens.push_back(token);
        }
    }

    Parser p{tokens};
    cout << p.parser()->evaluate() << endl;
    cout << "Index ist: " << p.idx << endl;
    return 0;
}
