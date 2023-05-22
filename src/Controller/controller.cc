#include "controller.h"

void Controller::ParseObjFile(const char *path) {
    facade_->ParseObjFile(path);
}

Elements *Controller::get_elements() {
    return facade_->get_elements();
}

void Controller::RotateCoordinates(double x, double y, double z) {
    facade_->GeometryRotate(x,y,z);
}
void Controller::ScaleCoordinates(double scaler) {
    facade_->GeometryScale(scaler);
}
void Controller::MoveCoordinates(double x, double y, double z) {
    facade_->GeometryMove(x,y,z);
}

void Controller::UndoPreviousChange() {
    facade_->UndoPreviousChange();
}
