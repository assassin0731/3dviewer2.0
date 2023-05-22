#include "obj_model.h"
#include "facade.h"
#include <iostream>
#include <string>
#include <time.h>

int main() {
  const char *path = "../Models/one_million.obj";
  
  Facade facade;
  facade.ParseObjFile(path);
//  model.Print();
clock_t tStart = clock();
//clock_t tStart = clock();
//std::cout<<facade.get_elements()->vertex[0]<<std::endl;
facade.GeometryRotate(10,10,10);
printf("Time taken: %.4fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
//std::cout<<facade.get_elements()->vertex[0];
  return 0;
}
/*
#include "ParcerCC.h"
#include <iostream>
#include <string>
#include <sstream>

  Elements &ObjModel::get_elements() {
    return elements_;
  }
  void ObjModel::Parser(const char *path) {
    Clear();
    std::ifstream obj_file(path);
    if (obj_file.is_open()) {
      std::string str;
      while (getline(obj_file, str)) {
        std::vector<std::string> splited_str;
        MakeVectorOfString(str, splited_str);
        LoadCoordinatesOfVertex(splited_str);
        LoadIndexes(splited_str);
      }
    }
    obj_file.close();
    elements_.max_value *= 2;
  }

  void ObjModel::MakeVectorOfString(const std::string &str, std::vector<std::string> &splited_str) {
        std::string new_str;
        for (int i = 0; i < str.size(); ++i) {
          if (str[i] != ' ') {
            new_str.push_back(str[i]);
          } else if (!new_str.empty()) {
            splited_str.push_back(new_str);
            new_str.clear();
          }
        }
        splited_str.push_back(new_str);
  }

  void ObjModel::LoadCoordinatesOfVertex(const std::vector<std::string> &splited_str) {
    if (!splited_str.empty() && splited_str[0] == "v") {
      double x = stod(splited_str[1]);//тут надо проверять на число
      double y = stod(splited_str[2]);
      double z = stod(splited_str[3]);
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

  void ObjModel::LoadIndexes(const std::vector<std::string> &splited_str) {
        if (!splited_str.empty() && splited_str[0] == "f") {
          for (int i = 1; i < splited_str.size(); ++i) {
            std::istringstream converter_to_int{splited_str[i]};
            int first_index;
            if (splited_str[i][0] >= '0' && splited_str[i][0] <= '9') {
            int index;
            converter_to_int >> index;
            if (i == 1) {
              first_index = index;
              elements_.index.push_back(first_index - 1);
            } else {
              elements_.index.push_back(index - 1);
              elements_.index.push_back(index - 1);
            }
            }
            if (i == splited_str.size() - 1) {
              elements_.index.push_back(first_index - 1);
            }
          }
        }
  }

  void ObjModel::Clear() {
      elements_.index.clear();
      elements_.vertex.clear();
      elements_.max_value = 0;
  }

  void ObjModel::Print() {
    for (int i = 0; i < elements_.vertex.size(); ++i) {
      std::cout<<elements_.vertex[i]<<" ";
    }
    std::cout<<std::endl;
    for (int i = 0; i < elements_.index.size(); ++i) {
      std::cout<<elements_.index[i]<<" ";
    }
    std::cout<<std::endl;
    std::cout<<elements_.vertex.size()<<" "<<elements_.index.size();
  }

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
    elements_.vertex[i] = elements_.vertex[i] * scaler;
  }
}

void ObjModel::MoveCoordinates(double x, double y, double z) {
  for (int i = 0; i < elements_.vertex.size(); i += 3) {
    elements_.vertex[i] = elements_.vertex[i] + x;
    elements_.vertex[i + 1] = elements_.vertex[i + 1] + y;
    elements_.vertex[i + 2] = elements_.vertex[i + 2] + z;
  }
}
*/