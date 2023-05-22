#ifndef CPP3_3VIEWER_V2_0_MODEL_OBJ_MODEL_H_
#define CPP3_3VIEWER_V2_0_MODEL_OBJ_MODEL_H_


#include <vector>
#include <fstream>
#include "../Matrix/s21_matrix_oop.h"

struct Elements {
  std::vector<double> vertex;
  std::vector<int> index;
  double max_value = 0;
};

class ObjModel {
  public:
    static ObjModel& get_instance()
    {
        static ObjModel    instance;
        return instance;}
    ObjModel(ObjModel const &other)               = delete;
    void operator=(ObjModel const &other)  = delete;

  Elements &get_elements();
  void ParseObjFile(const char *path);
  void Print();
  //void RotateCoordinates(double x, double y, double z);
  //void ScaleCoordinates(double scaler);
  //void MoveCoordinates(double x, double y, double z);

  private:


  ObjModel(){
    //matrix.setRows(1);
    //move_matrix.setRows(1);
  };
  /*
  S21Matrix matrix;
  S21Matrix rotate_matrix;
  S21Matrix move_matrix;
  */
  void LoadCoordinatesOfVertex(const char *line);
  //void SetRotateMatrix(double x, double y, double z);
  //void SetMoveMatrix(double x, double y, double z);
  void LoadIndexes(char *line);
  double SetMaxValue(double x, double y, double z);
  void Clear();
  Elements elements_;

};


#endif // CPP3_3VIEWER_V2_0_VIEW_OBJ_MODEL_H_
