#include "geometry.h"


void Geometry::set_elements(Elements *elements) {
    elements_ = elements;
    center_.x = 0;
    center_.y = 0;
    center_.z = 0;
}

Elements *Geometry::get_elements() {
    return elements_;
}

void Geometry::RotateCoordinates(double x, double y, double z, bool rotate_back) {
  CommandRotateMatrix rotate_matrix(elements_, &center_, x, y, z, rotate_back);
  rotate_matrix.Execute();
}

void Geometry::ScaleCoordinates(double scaler) {
    CommandScaleMatrix scale_matrix(elements_, &center_, scaler);
    scale_matrix.Execute();
}

void Geometry::MoveCoordinates(double x, double y, double z) {
    CommandMoveMatrix move_matrix(elements_, &center_, x, y, z);
    move_matrix.Execute();
}
