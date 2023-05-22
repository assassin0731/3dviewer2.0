#ifndef CPP3_3VIEWER_V2_0_MODEL_GEOMETRY_H_
#define CPP3_3VIEWER_V2_0_MODEL_GEOMETRY_H_
#include "obj_model.h"
#include "command.h"


class Geometry
{
public:
    static Geometry& get_instance()
    {
        static Geometry instance;
        return instance;}
    Geometry(Geometry const &other)      = delete;
    void operator=(Geometry const &other)  = delete;

    void set_elements(Elements *elements);

    Elements *get_elements();

    void RotateCoordinates(double x, double y, double z, bool rotate_back);
    void ScaleCoordinates(double scaler);
    void MoveCoordinates(double x, double y, double z);

private:
    Geometry(){};
    Elements *elements_;
    CoordCenter center_;
};

#endif // CPP3_3VIEWER_V2_0_MODEL_GEOMETRY_H_
