#include "IntMatrix.h"

IntMatrix::IntMatrix(size_t r, size_t c) : numRows(r), numColumns(c) {
  for (size_t i = 0; i < numRows; i++) {
    std::vector<int> row(c);
    rows.push_back(row);
  }
}

IntMatrix::IntMatrix(const IntMatrix & rhs) :
    numRows(rhs.numRows), numColumns(rhs.numColumns), rows(rhs.rows) {
}

IntMatrix::~IntMatrix() {
}

IntMatrix & IntMatrix::operator=(const IntMatrix & rhs) {
  numRows = rhs.numRows;
  numColumns = rhs.numColumns;
  rows = rhs.rows;
  return *this;
}

size_t IntMatrix::getRows() const {
  return numRows;
}

size_t IntMatrix::getColumns() const {
  return numColumns;
}

const std::vector<int> & IntMatrix::operator[](size_t index) const {
  assert((0 <= index) && (index < numRows));
  return rows[index];
}

std::vector<int> & IntMatrix::operator[](size_t index) {
  assert((0 <= index) && (index < numRows));
  return rows[index];
}

bool IntMatrix::operator==(const IntMatrix & rhs) const {
  bool equal = true;
  if ((numRows != rhs.numRows) || (numColumns != rhs.numColumns) || (rows != rhs.rows)) {
    equal = false;
  }
  return equal;
}

IntMatrix IntMatrix::operator+(const IntMatrix & rhs) const {
  assert((numRows == rhs.numRows) && (numColumns == rhs.numColumns));
  IntMatrix sum(numRows, numColumns);
  for (size_t i = 0; i < numRows; i++) {
    for (size_t j = 0; j < numColumns; j++) {
      sum[i][j] = rows[i][j] + rhs[i][j];
    }
  }
  return sum;
}

std::ostream & operator<<(std::ostream & s, const std::vector<int> & rhs) {
  s << "{";
  for (size_t i = 0; i < rhs.size(); i++) {
    s << rhs[i];
    if (i < rhs.size() - 1) {
      s << ", ";
    }
  }
  s << "}";
  return s;
}
std::ostream & operator<<(std::ostream & s, const IntMatrix & rhs) {
  s << "[ ";
  for (size_t i = 0; i < rhs.getRows(); i++) {
    s << rhs[i];
    if (i < rhs.getRows() - 1) {
      s << ",\n";
    }
  }
  s << " ]";
  return s;
}
