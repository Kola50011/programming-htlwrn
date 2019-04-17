#include <string>
#include <iostream>
#include <vector>
#include <regex>
#include <stack>

#include "expressions.hpp"

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

    // Tokanize
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
    tokens.push_back("_");

    // Build tree
    stack<Expression *> expressionStack;
    for (unsigned int i{0}; i < tokens.size() - 1; i++)
    {
        auto token = tokens[i];
        auto next = tokens[i + 1];

        cout << "Token: " << token << " Next: " << next << endl;

        if (token == string{"+"})
        {
            Addition *addition = new Addition{EMPTY_TERMINAL, EMPTY_TERMINAL};
            addition->setLeft(expressionStack.top());
            expressionStack.pop();
            expressionStack.push(addition);
        }
        else if (token == string{"-"})
        {
            Substraction *substraction = new Substraction{EMPTY_TERMINAL, EMPTY_TERMINAL};
            substraction->setLeft(expressionStack.top());
            expressionStack.pop();
            expressionStack.push(substraction);
        }
        else
        {
            Terminal *terminal = new Terminal{stod(token)};
            if (expressionStack.empty()) {
                expressionStack.push(terminal);
            } else {
                Expression* expression = expressionStack.top();
                expression->setRight(terminal);
            }
        }
    }
    cout << "Len: " << expressionStack.size() << endl;
    cout << "Result: " << expressionStack.top()->evaluate() << endl;
    return 0;
}
