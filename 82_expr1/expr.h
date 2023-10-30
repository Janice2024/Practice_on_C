#include <cstdlib>
#include <sstream>

class Expression {
 public:
  virtual std::string toString() const = 0;
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
  virtual ~NumExpression() {}
};

class PlusExpression : public Expression {
 private:
  Expression * lhs;
  Expression * rhs;

 public:
  PlusExpression(Expression * newLhs, Expression * newRhs) : lhs(newLhs), rhs(newRhs) {}
  std::string toString() const {
    std::stringstream stream;
    stream << "(" << lhs->toString() << "+" << rhs->toString() << ")";
    return stream.str();
  }
  virtual ~PlusExpression() {
    delete lhs;
    delete rhs;
  }
};
