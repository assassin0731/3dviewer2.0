#include "command.h"

Command::Command(Elements *elements, CoordCenter *center) : elements_(elements), center_(center){};

CommandRotateMatrix::CommandRotateMatrix(Elements *elements, CoordCenter *center, double x, double y, double z, bool rotate_back) : Command(elements, center) {
    S21Matrix x_matrix(3, 3);
    S21Matrix y_matrix(3, 3);
    S21Matrix z_matrix(3, 3);

    x_matrix(0,0) = 1;
    x_matrix(1,1) = cos(x);
    x_matrix(1,2) = -sin(x);
    x_matrix(2,1) = sin(x);
    x_matrix(2,2) = cos(x);

    y_matrix(0,0) = cos(y);
    y_matrix(0,2) = sin(y);
    y_matrix(1,1) = 1;
    y_matrix(2,0) = -sin(y);
    y_matrix(2,2) = cos(y);

    z_matrix(0,0) = cos(z);
    z_matrix(0,1) = -sin(z);
    z_matrix(1,0) = sin(z);
    z_matrix(1,1) = cos(z);
    z_matrix(2,2) = 1;
    if (!rotate_back) {
        rotate_matrix_ = x_matrix;
        rotate_matrix_.MulMatrix(y_matrix);
        rotate_matrix_.MulMatrix(z_matrix);
    } else {
        rotate_matrix_ = z_matrix;
        rotate_matrix_.MulMatrix(y_matrix);
        rotate_matrix_.MulMatrix(x_matrix);
    }
}

void CommandRotateMatrix::Execute() {
    S21Matrix this_matrix(1, 3);
    for (size_t i = 0; i < elements_->vertex.size(); i+=3) {
        this_matrix(0,0) = elements_->vertex[i] - center_->x;
        this_matrix(0,1) = elements_->vertex[i+1] - center_->y;
        this_matrix(0,2) = elements_->vertex[i+2] - center_->z;
        this_matrix *= rotate_matrix_;
        elements_->vertex[i] = this_matrix(0,0) + center_->x;
        elements_->vertex[i+1] = this_matrix(0,1) + center_->y;
        elements_->vertex[i+2] = this_matrix(0,2) + center_->z;
    }
}

CommandScaleMatrix::CommandScaleMatrix(Elements *elements, CoordCenter *center, double scaler) : Command(elements, center) {
    scaler_ = scaler;
}

void CommandScaleMatrix::Execute() {
    S21Matrix this_matrix(1, 3);
    for (size_t i = 0; i < elements_->vertex.size(); i+=3) {
        this_matrix(0,0) = elements_->vertex[i]  - center_->x;
        this_matrix(0,1) = elements_->vertex[i+1]  - center_->y;
        this_matrix(0,2) = elements_->vertex[i+2] - center_->z;
        this_matrix *= scaler_;
        elements_->vertex[i] = this_matrix(0,0) + center_->x;
        elements_->vertex[i+1] = this_matrix(0,1) + center_->y;
        elements_->vertex[i+2] = this_matrix(0,2) + center_->z;
    }
}

CommandMoveMatrix::CommandMoveMatrix(Elements *elements, CoordCenter *center, double x, double y, double z) : Command(elements, center) {
    move_matrix_(0,0) = x;
    move_matrix_(0,1) = y;
    move_matrix_(0,2) = z;
    center_->x += x;
    center_->y += y;
    center_->z += z;
}

void CommandMoveMatrix::Execute() {
    S21Matrix this_matrix(1, 3);
    for (size_t i = 0; i < elements_->vertex.size(); i+=3) {
        this_matrix(0,0) = elements_->vertex[i];
        this_matrix(0,1) = elements_->vertex[i+1];
        this_matrix(0,2) = elements_->vertex[i+2];
        this_matrix += move_matrix_;
        elements_->vertex[i] = this_matrix(0,0);
        elements_->vertex[i+1] = this_matrix(0,1);
        elements_->vertex[i+2] = this_matrix(0,2);
    }
}
