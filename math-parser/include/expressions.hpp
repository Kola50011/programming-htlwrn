#ifndef EXPRESSIONS_HPP
#define EXPRESSIONS_HPP

#include <string>

class Expression
{
  public:
    virtual double evaluate() = 0;
    virtual ~Expression() = 0; // Virtual deconstructor definieren, cauz: ‘class Expression’ has virtual functions and accessible non-virtual destructor
};

class Addition : public Expression
{
  public:
    Addition(Expression &_left, Expression &_right) : left{_left}, right{_right} {};
    double evaluate() override
    {
        return left.evaluate() + right.evaluate();
    };

  private:
    Expression &left;
    Expression &right;
};

class Substraction : public Expression
{
  public:
    Substraction(Expression &_left, Expression &_right) : left{_left}, right{_right} {};
    double evaluate() override
    {
        return left.evaluate() - right.evaluate();
    };

  private:
    Expression &left;
    Expression &right;
};

class Multiplication : public Expression
{
  public:
    Multiplication(Expression &_left, Expression &_right) : left{_left}, right{_right} {};
    double evaluate() override
    {
        return left.evaluate() * right.evaluate();
    };

  private:
    Expression &left;
    Expression &right;
};

class Division : public Expression
{
  public:
    Division(Expression &_left, Expression &_right) : left{_left}, right{_right} {};
    double evaluate() override
    {
        return left.evaluate() / right.evaluate();
    };

  private:
    Expression &left;
    Expression &right;
};

class Terminal : public Expression
{
  public:
    Terminal(double _num) : num{_num} {}
    double evaluate() override
    {
        return num;
    };

  private:
    double num;
};

#endif