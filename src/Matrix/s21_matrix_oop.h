#ifndef CPP3_3VIEWER_V2_0_MATRIX_S21_MATRIX_OOP_H_
#define CPP3_3VIEWER_V2_0_MATRIX_S21_MATRIX_OOP_H_

#include <cmath>
#include <iostream>

class S21Matrix {

 public:
  S21Matrix();
  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix &other) = delete;
  S21Matrix(S21Matrix &&other);
  ~S21Matrix();

  void SumMatrix(const S21Matrix &other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix &other);

  // Operators
  S21Matrix &operator=(const S21Matrix &other);
  S21Matrix &operator=(S21Matrix &&other) = delete;
  S21Matrix &operator+=(const S21Matrix &other);
  S21Matrix &operator*=(const S21Matrix &other);
  S21Matrix &operator*=(const double num);
  double &operator()(int row, int col);

private:
 int rows_;
 int cols_;
 double **matrix_;
  // Help functions
  void Create();
  void Copy(const S21Matrix &other);
  void Remove();

};

#endif  //  CPP3_3VIEWER_V2_0_MATRIX_S21_MATRIX_OOP_H_
