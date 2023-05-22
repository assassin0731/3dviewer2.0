#ifndef CPP3_3VIEWER_V2_0_CONTROLLER_CONTROLLER_H_
#define CPP3_3VIEWER_V2_0_CONTROLLER_CONTROLLER_H_

#include "../Model/obj_model.h"
#include "../Model/facade.h"

class Controller {
 public:
  Controller(Facade *facade) : facade_(facade) {};
  void ParseObjFile(const char *path);
  Elements *get_elements();
  void RotateCoordinates(double x, double y, double z);
  void ScaleCoordinates(double scaler);
  void MoveCoordinates(double x, double y, double z);
  void UndoPreviousChange();

 private:
  Facade *facade_;
};


#endif  // CPP3_3VIEWER_V2_0_CONTROLLER_CONTROLLER_H_
