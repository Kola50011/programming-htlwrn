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
    Parser(vector<string> &_tokens) : tokens{_tokens} {}
    int idx{0};
    vector<string> &tokens;

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
    }

    Expression *binary(string token)
    {
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
        else
        {
            return new Exponent();
        }
    }

    void expect(string token)
    {
        if (tokens[idx] != token)
        {
            throw logic_error("Syntax error");
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

    Expression *parser()
    { // E
        Expression *t = T();
        auto next = tokens[idx];
        while (next == string{"+"} || next == string{"-"})
        {
            auto *operation = binary(next);
            consume();
            auto *t1 = T();
            t = mkNode(operation, t, t1);
            next = tokens[idx];
        }
        return t;
    }

    Expression *P()
    {
        Expression *t = nullptr;
        auto next = tokens[idx];
        if (isNumber(next))
        {
            t = new Terminal(stod(next));
            consume();
            return t;
        }
        else if (next == string{"("})
        {
            consume();
            t = parser();
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
            throw logic_error("ERROR");
        }
    }

    Expression *F()
    {
        auto *t = P();
        auto next = tokens[idx];
        if (next == string{"^"})
        {
            consume();
            auto *t1 = F();
            return mkNode(binary(next), t, t1);
        }
        else
        {
            return t;
        }
    }

    Expression *T()
    {
        Expression *t = F();
        auto next = tokens[idx];
        while (next == string{"*"} || next == string{"/"})
        {
            auto *operation = binary(next);
            consume();
            auto *t1 = F();
            t = mkNode(operation, t, t1);
            next = tokens[idx];
        }
        return t;
    }
};