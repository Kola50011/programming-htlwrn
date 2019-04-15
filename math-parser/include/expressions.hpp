#ifndef EXPRESSIONS_HPP
#define EXPRESSIONS_HPP

#include <string>

class expression {
public:
    virtual double evaluate() = 0;
};

class addition : public expression {
public:
    addition(expression& exp1, expression& exp2) : lhs{exp1}, rhs{exp2} {};
    double evaluate() override {
        return lhs.evaluate() + rhs.evaluate();
    };

private:
    expression& lhs;
    expression& rhs;
};

class substraction : public expression {
public:
    substraction(expression& exp1, expression& exp2) : lhs{exp1}, rhs{exp2} {};
    double evaluate() override {
        return lhs.evaluate() - rhs.evaluate();
    };
private:
    expression& lhs;
    expression& rhs;    
};

class multiplication : public expression {
public:
    multiplication(expression& exp1, expression& exp2) : lhs{exp1}, rhs{exp2} {};
    double evaluate() override {
        return lhs.evaluate() * rhs.evaluate();
    };
private:
    expression& lhs;
    expression& rhs;    
};

class division : public expression {
public:
    division(expression& exp1, expression& exp2) : lhs{exp1}, rhs{exp2} {};
    double evaluate() override {
        return lhs.evaluate() / rhs.evaluate();
    };
private:
    expression& lhs;
    expression& rhs;    
};

class terminal : public expression {
public:
    terminal(std::string num) {}
    double evaluate() override {
        return num;
    };
private:
    double num;
};

#endif