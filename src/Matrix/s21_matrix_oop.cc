#include "s21_matrix_oop.h"

S21Matrix::S21Matrix() : rows_(1), cols_(3) { Create(); }

S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  if (rows < 1 || cols < 1) {
    throw std::out_of_range("Rows or columns are less then 1");
  }
  Create();
}

S21Matrix::S21Matrix(S21Matrix &&other) {
  rows_ = other.rows_;
  cols_ = other.cols_;
  matrix_ = other.matrix_;
  other.matrix_ = nullptr;
  other.cols_ = other.rows_ = 0;
}

S21Matrix::~S21Matrix() { Remove(); }

void S21Matrix::SumMatrix(const S21Matrix &other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::out_of_range("Different rows or cols");
  }
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] += other.matrix_[i][j];
    }
  }
}

void S21Matrix::MulNumber(const double num) {
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] *= num;
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix &other) {
  if (cols_ != other.rows_) {
    throw std::out_of_range("Cols of first doesn't match rows of second");
  }
  S21Matrix tmp((S21Matrix &&) * this);
  rows_ = tmp.rows_;
  cols_ = other.cols_;
  Create();
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      for (int k = 0; k < tmp.cols_; k++) {
        matrix_[i][j] += tmp.matrix_[i][k] * other.matrix_[k][j];
      }
    }
  }
}
