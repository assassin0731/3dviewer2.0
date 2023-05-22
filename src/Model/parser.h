#ifndef MAIN_H
#define MAIN_H
#include <locale.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Struct {
  double *vertex;
  int *index;
  int vertex_counter;
  int index_counter;
  double max_value;
} Elements;

void ElementCounter(const char *file_name, Elements *elements);
void parserr(const char *file_name, Elements *elements);
void Parser(Elements *elements, const char *path);
void RotationC(Elements *elements, double x, double y, double z);
void ScalingC(Elements *elements, double scaler);
void MovingC(Elements *elements, double x, double y, double z);

#endif // MAIN_H
