#include "facade.h"

Facade::Facade() {
    model_ = &ObjModel::get_instance();
    geometry_ = &Geometry::get_instance();
    geometry_->set_elements(&model_->get_elements());
}

Elements *Facade::get_elements() {
    return geometry_->get_elements();
}

void Facade::ParseObjFile (const char *path) {
    prev_state_.get_position().clear();
    model_->ParseObjFile(path);
}

void Facade::GeometryRotate(double x, double y, double z) {
    prev_state_.get_position().push_back({-x, -y, -z, TypeOfChange::kRotate});
    geometry_->RotateCoordinates(x, y, z, false);
}

void Facade::GeometryScale(double scaler) {
    prev_state_.get_position().push_back({1./scaler, 0, 0, TypeOfChange::kScale});
    geometry_->ScaleCoordinates(scaler);
}

void Facade::GeometryMove(double x, double y, double z) {
    prev_state_.get_position().push_back({-x, -y, -z, TypeOfChange::kMove});
    geometry_->MoveCoordinates(x, y, z);
}

void Facade::UndoPreviousChange(){
    if (!prev_state_.get_position().empty()) {
        if (prev_state_.get_position().back().type == TypeOfChange::kRotate) {
            geometry_->RotateCoordinates(prev_state_.get_position().back().x, prev_state_.get_position().back().y, prev_state_.get_position().back().z, true);
        } else if (prev_state_.get_position().back().type == TypeOfChange::kMove) {
            geometry_->MoveCoordinates(prev_state_.get_position().back().x, prev_state_.get_position().back().y, prev_state_.get_position().back().z);
        } else {
            geometry_->ScaleCoordinates(prev_state_.get_position().back().x);
        }
    prev_state_.get_position().pop_back();
    }

}
