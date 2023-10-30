#include <cstdlib>
#include <sstream>

class Expression {
 public:
  virtual std::string toString() const = 0;
  virtual long evaluate() const = 0;
  virtual ~Expression() {}
};

class NumExpression : public Expression {
 private:
  long number;

 public:
  NumExpression(long n) : number(n) {}
  virtual std::string toString() const {
    std::stringstream stream;
    stream << number;
    return stream.str();
  }
  virtual long evaluate() const { return number; }
  virtual ~NumExpression() {}
};

class Operation : public Expression {
 private:
  char sign;
  Expression * lhs;
  Expression * rhs;

 public:
  Operation(char newSign, Expression * newLhs, Expression * newRhs) :
      sign(newSign), lhs(newLhs), rhs(newRhs) {}
  virtual std::string toString() const {
    std::stringstream stream;
    stream << '(' << lhs->toString() << ' ' << sign << ' ' << rhs->toString() << ')';
    return stream.str();
  }
  virtual long evaluate() const {
    switch (sign) {
      case '+':
        return (lhs->evaluate() + rhs->evaluate());
      case '-':
        return (lhs->evaluate() - rhs->evaluate());
      case '*':
        return (lhs->evaluate() * rhs->evaluate());
      case '/':
        return (lhs->evaluate() / rhs->evaluate());
      default:
        std::cerr << "Impossible op char: " << sign << "\n";
        abort();
    }
  }
  virtual ~Operation() {
    delete lhs;
    delete rhs;
  }
};

class PlusExpression : public Operation {
 public:
  PlusExpression(Expression * lhs, Expression * rhs) : Operation('+', lhs, rhs) {}
};

class MinusExpression : public Operation {
 public:
  MinusExpression(Expression * lhs, Expression * rhs) : Operation('-', lhs, rhs) {}
};

class TimesExpression : public Operation {
 public:
  TimesExpression(Expression * lhs, Expression * rhs) : Operation('*', lhs, rhs) {}
};

class DivExpression : public Operation {
 public:
  DivExpression(Expression * lhs, Expression * rhs) : Operation('/', lhs, rhs) {}
};
