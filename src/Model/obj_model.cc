#include "obj_model.h"
#include <iostream>
#include <string>
#include <sstream>
#include <string.h>
#include <locale>
#include "../Matrix/s21_matrix_oop.h"
#include "command.h"

  Elements &ObjModel::get_elements() {
    return elements_;
  }
  void ObjModel::ParseObjFile(const char *path) {
    setlocale(LC_ALL, "en-US");
    setlocale(LC_NUMERIC, "C");
    Clear();
    FILE *file = fopen(path, "r");
    if (file != NULL) {
      char *line = NULL;
      size_t len = 0;
      while (getline(&line, &len, file) != EOF) {
        LoadCoordinatesOfVertex(line);
        LoadIndexes(line);
      }
      free(line);
    }
    fclose(file);
    elements_.max_value *= 2;
  }

  void ObjModel::LoadCoordinatesOfVertex(const char *line) {
    if (line[0] == 'v' && line[1] == ' ') {
      double x, y, z;
      char str[3];
      // std::stringstream stream(line);  почти в 2 раза дольше сканфа
      // stream >> str >> x >> y >> z;
      sscanf(line, " %s %lf %lf %lf", str, &x, &y, &z);
      elements_.vertex.push_back(x);
      elements_.vertex.push_back(y);
      elements_.vertex.push_back(z);
      elements_.max_value = SetMaxValue(x ,y, z);
    }
  }

  double ObjModel::SetMaxValue(double x, double y, double z) {
    double return_value = elements_.max_value;
      if (fabs(x) > return_value) {
        return_value = fabs(x);
      }
      if (fabs(y) > return_value) {
        return_value = fabs(y);
      }
      if (fabs(z) > return_value) {
        return_value = fabs(z);
      }
      return return_value;
  }

  void ObjModel::LoadIndexes(char *line) {
        if (line[0] == 'f' && line[1] == ' ') {
          char sep[2] = " ";
          char *istr = strtok(line, sep);
          int first = -1;
          while (istr != NULL) {
            if (isdigit(*istr)) {
              int index;
              sscanf(istr, "%d", &index);
              elements_.index.push_back(index - 1);
              if (first == -1) {
                first = index - 1;
              } else {
                elements_.index.push_back(index - 1);
              }
            }
            istr = strtok(NULL, sep);
          }
          if (first != -1) {
          elements_.index.push_back(first);
        }
        }
  }

  void ObjModel::Clear() {
      elements_.index.clear();
      elements_.vertex.clear();
      elements_.max_value = 0;
  }

  void ObjModel::Print() {
    for (size_t i = 0; i < elements_.vertex.size(); ++i) {
      std::cout<<elements_.vertex[i]<<" ";
    }
    std::cout<<std::endl;
    for (size_t i = 0; i < elements_.index.size(); ++i) {
      std::cout<<elements_.index[i]<<" ";
    }
    std::cout<<std::endl;
    std::cout<<elements_.vertex.size()<<" "<<elements_.index.size();
  }
/*
void ObjModel::RotateCoordinates(double x, double y, double z) {

  CommandRotateMatrix rotate_matrix(x, y, z);
  for (int i = 0; i < elements_.vertex.size(); i += 3) {
      rotate_matrix.SetElements(elements_.vertex[i], elements_.vertex[i+1], elements_.vertex[i+2]);
      rotate_matrix.RotateMatrix(elements_.vertex[i], elements_.vertex[i+1], elements_.vertex[i+2]);
  }

  SetRotateMatrix(x, y, z);
  for (int i = 0; i < elements_.vertex.size(); i += 3) {
    matrix(0,0) = elements_.vertex[i];
    matrix(0,1) = elements_.vertex[i+1];
    matrix(0,2) = elements_.vertex[i+2];
    matrix *= rotate_matrix;
    elements_.vertex[i] = matrix(0,0);
    elements_.vertex[i+1] = matrix(0,1);
    elements_.vertex[i+2] = matrix(0,2);
  }

}
  */
/*
void ObjModel::SetRotateMatrix(double x, double y, double z) {
  rotate_matrix(0, 0) = cos(y)*cos(z);
  rotate_matrix(0, 1) = -sin(z)*cos(y);
  rotate_matrix(0, 2) = sin(y);
  rotate_matrix(1, 0) = sin(x)*sin(y)*cos(z)+sin(z)*cos(x);
  rotate_matrix(1, 1) = -sin(x)*sin(y)*sin(z)+cos(x)*cos(z);
  rotate_matrix(1, 2) = -sin(x)*cos(y);
  rotate_matrix(2, 0) = sin(x)*sin(z) - sin(y)*cos(x)*cos(z);
  rotate_matrix(2, 1) = sin(x)*cos(z) + sin(y)*sin(z)*cos(x);
  rotate_matrix(2, 2) = cos(x)*cos(y);
}
*/
      /*
void ObjModel::ScaleCoordinates(double scaler) {
    CommandScaleMatrix scale_matrix(scaler);
    for (int i = 0; i < elements_.vertex.size(); i += 3) {
        scale_matrix.SetElements(elements_.vertex[i], elements_.vertex[i+1], elements_.vertex[i+2]);
        scale_matrix.ScaleMatrix(elements_.vertex[i], elements_.vertex[i+1], elements_.vertex[i+2]);
    }
    */
    /*
  for (int i = 0; i < elements_.vertex.size(); i += 3) {
    matrix(0,0) = elements_.vertex[i];
    matrix(0,1) = elements_.vertex[i+1];
    matrix(0,2) = elements_.vertex[i+2];
    matrix *= scaler;
    elements_.vertex[i] = matrix(0,0);
    elements_.vertex[i+1] = matrix(0,1);
    elements_.vertex[i+2] = matrix(0,2);
  }
  */
//}
/*
void ObjModel::MoveCoordinates(double x, double y, double z) {

    CommandMoveMatrix move_matrix(x, y, z);
    for (int i = 0; i < elements_.vertex.size(); i += 3) {
        move_matrix.SetElements(elements_.vertex[i], elements_.vertex[i+1], elements_.vertex[i+2]);
        move_matrix.MoveMatrix(elements_.vertex[i], elements_.vertex[i+1], elements_.vertex[i+2]);
    }
    */
/*
  SetMoveMatrix(x,y,z);
  for (int i = 0; i < elements_.vertex.size(); i += 3) {
    matrix(0,0) = elements_.vertex[i];
    matrix(0,1) = elements_.vertex[i+1];
    matrix(0,2) = elements_.vertex[i+2];
    matrix += move_matrix;
    elements_.vertex[i] = matrix(0,0);
    elements_.vertex[i+1] = matrix(0,1);
    elements_.vertex[i+2] = matrix(0,2);
  }
  */
//}
/*
void ObjModel::SetMoveMatrix(double x, double y, double z) {
  move_matrix(0,0) = x;
  move_matrix(0,1) = y;
  move_matrix(0,2) = z;
}
*/
/*
void ObjModel::RotateCoordinates(double x, double y, double z) {
  for (int i = 0; i < elements_.vertex.size(); i += 3) {
    double temp_y = elements_.vertex[i + 1];
    double temp_z = elements_.vertex[i + 2];
    elements_.vertex[i + 1] = cos(x) * temp_y - sin(x) * temp_z;
    elements_.vertex[i + 2] = sin(x) * temp_y + cos(x) * temp_z;
  }
  for (int i = 0; i < elements_.vertex.size(); i += 3) {
    double temp_x = elements_.vertex[i];
    double temp_z = elements_.vertex[i + 2];
    elements_.vertex[i] = cos(y) * temp_x - sin(y) * temp_z;
    elements_.vertex[i + 2] = sin(y) * temp_x + cos(y) * temp_z;
  }
  for (int i = 0; i < elements_.vertex.size(); i += 3) {
    double temp_x = elements_.vertex[i];
    double temp_y = elements_.vertex[i + 1];
    elements_.vertex[i] = cos(z) * temp_x - sin(z) * temp_y;
    elements_.vertex[i + 1] = sin(z) * temp_x + cos(z) * temp_y;
  }
}


void ObjModel::ScaleCoordinates(double scaler) {
  for (int i = 0; i < elements_.vertex.size(); i++) {
    elements_.vertex[i] *= scaler;
  }
}

void ObjModel::MoveCoordinates(double x, double y, double z) {
  for (int i = 0; i < elements_.vertex.size(); i += 3) {
    elements_.vertex[i] += x;
    elements_.vertex[i + 1] += y;
    elements_.vertex[i + 2] += z;
  }
}
*/
