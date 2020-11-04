// http://www.engr.mun.ca/~theo/Misc/exp_parsing.htm
#include <string>
#include <iostream>
#include <vector>
#include <regex>
#include <stack>

#include "expressions.hpp"
#include "parser.hpp"

using namespace std;

void cleanup(string &input)
{
    std::regex token_re{"\\+|-|\\(|\\)|/|\\*"};
    std::regex whitespace{"\\ +"};
    input = std::regex_replace(input, token_re, " $& ");
    input = std::regex_replace(input, whitespace, " ");
}

vector<string> tokenize(string &input)
{
    istringstream inputStream{input};
    string token;
    vector<string> tokens;
    while (getline(inputStream, token, ' '))
    {
        if (token != string{" "} || token != string{""})
        {
            tokens.push_back(token);
        }
    }

    tokens.erase(remove_if(tokens.begin(), tokens.end(), [](auto s) { return s == string{""}; }), tokens.end());
    tokens.push_back("end");
    return tokens;
}

int main(int argc, const char *argv[])
{
    if (argc != 2)
    {
        cout << "Please provide exactly 1 argument with the mathematical expression!" << endl;
        return 1;
    }

    string input = argv[1];
    cleanup(input);
    auto tokens = tokenize(input);
    Parser p{tokens};

    cout << "Input: " << input << endl;
    auto result = to_string(p.parse());
    cout << "Result: " << result << endl;
    return 0;
}
