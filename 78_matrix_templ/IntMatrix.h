#ifndef __INT_MATRIX_H__
#define __INT_MATRIX_H__

#include <assert.h>

#include <cstdlib>
#include <iostream>
#include <vector>

class IntMatrix {
 private:
  // WRITE ME
  size_t numRows;
  size_t numColumns;
  std::vector<std::vector<int> > rows;

 public:
  IntMatrix() : numRows(0), numColumns(0){};
  IntMatrix(size_t r, size_t c);
  IntMatrix(const IntMatrix & rhs);
  ~IntMatrix();
  IntMatrix & operator=(const IntMatrix & rhs);
  size_t getRows() const;
  size_t getColumns() const;
  const std::vector<int> & operator[](size_t index) const;
  std::vector<int> & operator[](size_t index);
  bool operator==(const IntMatrix & rhs) const;
  IntMatrix operator+(const IntMatrix & rhs) const;

  friend std::ostream & operator<<(std::ostream & s, const IntMatrix & rhs);
};

#endif
