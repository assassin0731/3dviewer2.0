#ifndef CPP3_3VIEWER_V2_0_MODEL_FACADE_H_
#define CPP3_3VIEWER_V2_0_MODEL_FACADE_H_
#include "obj_model.h"
#include "geometry.h"
#include "memento.h"



class Facade
{
public:
    Facade();

    Elements *get_elements();

    void ParseObjFile (const char *path);

    void GeometryRotate(double x, double y, double z);
    void GeometryScale(double scaler);
    void GeometryMove(double x, double y, double z);

    void UndoPreviousChange();

private:
    ObjModel *model_;
    Geometry *geometry_;
    Memento prev_state_;
   // std::vector<PrevPosition> prev_pos_;
};

#endif // CPP3_3VIEWER_V2_0_MODEL_FACADE_H_
