#pragma once

#include <string>
#include <cmath>

class Expression
{
public:
  virtual double evaluate() = 0;
  virtual ~Expression(){}; // Virtual deconstructor definieren, cauz: ‘class Expression’ has virtual functions and accessible non-virtual destructor
  virtual void setLeft(Expression *left) = 0;
  virtual void setRight(Expression *right) = 0;
};

class Terminal : public Expression
{
public:
  Terminal(double _num) : num{_num} {}
  Terminal() = default;
  virtual double evaluate()
  {
    return num;
  };

  void setNum(double _num)
  {
    num = _num;
  }

  virtual void setLeft(Expression *) {}
  virtual void setRight(Expression *) {}

private:
  double num;
};

class Addition : public Expression
{
public:
  Addition(Expression *_left = nullptr, Expression *_right = nullptr) : left{_left}, right{_right} {};
  virtual double evaluate()
  {
    return left->evaluate() + right->evaluate();
  };

  virtual void setLeft(Expression *_left)
  {
    left = _left;
  }
  virtual void setRight(Expression *_right)
  {
    right = _right;
  }

private:
  Expression *left;
  Expression *right;
};

class Substraction : public Expression
{
public:
  Substraction(Expression *_left = nullptr, Expression *_right = nullptr) : left{_left}, right{_right} {};
  virtual double evaluate()
  {
    return left->evaluate() - right->evaluate();
  };

  virtual void setLeft(Expression *_left)
  {
    left = _left;
  }
  virtual void setRight(Expression *_right)
  {
    right = _right;
  }

private:
  Expression *left;
  Expression *right;
};

class Multiplication : public Expression
{
public:
  Multiplication(Expression *_left = nullptr, Expression *_right = nullptr) : left{_left}, right{_right} {};
  virtual double evaluate()
  {
    return left->evaluate() * right->evaluate();
  };

  virtual void setLeft(Expression *_left)
  {
    left = _left;
  }
  virtual void setRight(Expression *_right)
  {
    right = _right;
  }

private:
  Expression *left;
  Expression *right;
};

class Division : public Expression
{
public:
  Division(Expression *_left = nullptr, Expression *_right = nullptr) : left{_left}, right{_right} {};
  virtual double evaluate()
  {
    return left->evaluate() / right->evaluate();
  };

  virtual void setLeft(Expression *_left)
  {
    left = _left;
  }
  virtual void setRight(Expression *_right)
  {
    right = _right;
  }

private:
  Expression *left;
  Expression *right;
};

double Expression::evaluate()
{
  return -1;
}

class Exponent : public Expression
{
public:
  Exponent(Expression *_left = nullptr, Expression *_right = nullptr) : left{_left}, right{_right} {};
  virtual double evaluate()
  {
    return std::pow(left->evaluate(), right->evaluate());
  };

  virtual void setLeft(Expression *_left)
  {
    left = _left;
  }
  virtual void setRight(Expression *_right)
  {
    right = _right;
  }

private:
  Expression *left;
  Expression *right;
};