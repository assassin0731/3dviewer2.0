#include "s21_matrix_oop.h"

void S21Matrix::Create() {
  matrix_ = new double *[rows_];
  for (int i = 0; i < rows_; ++i) {
    matrix_[i] = new double[cols_]();
  }
}

void S21Matrix::Remove() {
  for (int i = 0; i < rows_; ++i) {
    delete[] matrix_[i];
  }
  delete[] matrix_;
}

void S21Matrix::Copy(const S21Matrix &other) {
  rows_ = other.rows_;
  cols_ = other.cols_;
  Create();
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}
