#pragma once

#include "expressions.hpp"

#include <vector>
#include <string>
#include <exception>
#include <cmath>
#include <iostream>

using namespace std;

class Parser
{
  public:
    Parser(vector<string> &_tokens) : tokens{_tokens}
    {
        next = tokens[idx];
    }
    int idx{0};
    vector<string> &tokens;
    string next;

    // Helpers
    bool isNumber(const string &s)
    {
        try
        {
            stod(s);
            return true;
        }
        catch (...)
        {
            return false;
        }
    }

    void consume()
    {
        idx += 1;
        next = tokens[idx];
    }

    Expression *binary(string token)
    {
        cout << "Reading: " << token << endl;
        if (token == string{"+"})
        {
            return new Addition();
        }
        else if (token == string{"-"})
        {
            return new Substraction();
        }
        else if (token == string{"*"})
        {
            return new Multiplication();
        }
        else if (token == string{"/"})
        {
            return new Division();
        }
        else if (token == string{"^"})
        {
            return new Exponent();
        }
        else
        {
            throw logic_error("Invalid symbol encountered: " + next);
        }
    }

    void expect(string token)
    {
        if (tokens[idx] != token)
        {
            throw logic_error("Invalid symbol encountered: " + next);
        }
        else
        {
            consume();
        }
    }

    Expression *mkNode(Expression *operation, Expression *lhs, Expression *rhs)
    {
        operation->setLeft(lhs);
        operation->setRight(rhs);
        return operation;
    }

    double parse()
    {
        auto e = E();
        if (next != string{"end"})
        {
            throw logic_error("Invalid symbol encountered: " + next);
        }

        return e->evaluate();
    }
    
    // G:
    //     E --> T {( "+" | "-" ) T}
    //     T --> F {( "*" | "/" ) F}
    //     F --> P ["^" F]
    //     P --> v | "(" E ")" | "-" T

    Expression *E()
    { // E
        Expression *t = T();
        while (next == string{"+"} || next == string{"-"})
        {
            auto *operation = binary(next);
            consume();
            auto *t1 = T();
            t = mkNode(operation, t, t1);
        }
        return t;
    }

    Expression *T()
    {
        Expression *t = F();
        while (next == string{"*"} || next == string{"/"})
        {
            auto *operation = binary(next);
            consume();
            auto *t1 = F();
            t = mkNode(operation, t, t1);
        }
        return t;
    }

    Expression *F()
    {
        Expression *t = P();
        if (next == string{"^"})
        {
            auto *operation = binary(next);
            consume();
            auto *t1 = F();
            t = mkNode(operation, t, t1);
        }
        return t;
    }

    Expression *P()
    {
        Expression *t = nullptr;
        if (isNumber(next))
        {
            t = new Terminal(stod(next));
            consume();
            return t;
        }
        else if (next == string{"("})
        {
            consume();
            t = E();
            expect(")");
            return t;
        }
        else if (next == string{"-"})
        {
            consume();
            t = F();
            return mkNode(binary("-"), new Terminal{0}, t);
        }
        else
        {
            throw logic_error("Invalid symbol encountered: " + next);
        }
    }
};