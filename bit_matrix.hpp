#ifndef BIT_MATRIX_HPP
#define BIT_MATRIX_HPP

#include <algorithm>
#include <stdexcept>
#include <vector>
#include "boost/dynamic_bitset.hpp"

class Bit_Matrix {
 public:
  Bit_Matrix(int rows, int columns) : n_row_{rows}, n_column_{columns}, bitset_(rows*columns) {
      check_in_range(rows, columns);
  }

  Bit_Matrix(Bit_Matrix const& matrix)
      : n_row_{matrix.get_height()}, n_column_{matrix.get_length()} {
    bitset_.resize(n_row_ * n_column_);
    for (int i = 1; i <= matrix.get_height(); ++i) {
      for (int j = 1; j <= matrix.get_length(); ++j) {
        set_bit(i, j, matrix(i, j));
      }
    }
  }

  void check_in_range(int row, int column) const {
    if (row <= 0 || column <= 0) {
      throw std::out_of_range("inserted indexes "+ std::to_string(row) + " and "+ std::to_string(column) +" are not allowed. Negative or zero indexes not accepted");
    }
    if (row > n_row_ || column > n_column_)
      throw std::out_of_range("matrix is out of range, inserted indexes were:" + std::to_string(row) + " and " + std::to_string(column));
  };

  void set_bit(int row, int column, bool value) {
    check_in_range(row, column);
    bitset_[calculate_index(row, column)] = value;
  }

  bool operator()(int row, int column) const {
    check_in_range(row, column);
    return bitset_[calculate_index(row, column)];
  }

  boost::dynamic_bitset<> get_row(int row_index){
    check_in_range(row_index, 1);
    boost::dynamic_bitset<> row;
    row.reserve(n_column_);
    for(int column_index=1; column_index!=n_column_+1; ++column_index){
      row.push_back(bitset_[calculate_index(row_index, column_index)]);
    }
    return row;
  }

  void set_row(int row_index, boost::dynamic_bitset<> row){
    check_in_range(row_index, 1);
    for(int column_index=1; column_index!=n_column_+1; ++column_index){
      bitset_[calculate_index(row_index, column_index)] = row[column_index];
    }
  }


  void operator=(const Bit_Matrix& to_copy) {
    if (to_copy.get_height() != n_row_ || to_copy.get_length() != n_column_) {
      throw std::out_of_range("matrixes are incompatible for copy");
    }
    for (int i = 1; i <= n_row_; ++i) {
      for (int j = 1; j <= n_column_; ++j) {
        set_bit(i, j, to_copy(i, j));
      }
    }
  };

  int get_height() const { return n_row_; }
  int get_length() const { return n_column_; }

 private:
  int n_row_;
  int n_column_;
  boost::dynamic_bitset<> bitset_;

  int calculate_index(int row, int column) const {
    return n_column_ * (row - 1) + (column - 1);
  }
};


#endif