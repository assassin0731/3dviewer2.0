#ifndef CPP3_3VIEWER_V2_0_MODEL_COMMAND_H_
#define CPP3_3VIEWER_V2_0_MODEL_COMMAND_H_
#include "../Matrix/s21_matrix_oop.h"
#include <vector>
#include "obj_model.h"

struct CoordCenter {
    double x;
    double y;
    double z;
};

class Command
{
public:
    Command(Elements *elements, CoordCenter *center);
protected:
    Elements *elements_;
    CoordCenter *center_;
};

class CommandRotateMatrix : public Command
{
public:
    CommandRotateMatrix(Elements *elements, CoordCenter *center, double x, double y, double z, bool rotate_back);
    void Execute();

private:
    S21Matrix rotate_matrix_;
};

class CommandScaleMatrix : public Command
{
public:
    CommandScaleMatrix(Elements *elements, CoordCenter *center, double scaler);
    void Execute();

private:
    double scaler_;
};

class CommandMoveMatrix : public Command
{
public:
    CommandMoveMatrix(Elements *elements, CoordCenter *center, double x, double y, double z);
    void Execute();

private:
    S21Matrix move_matrix_;
};

#endif // CPP3_3VIEWER_V2_0_MODEL_COMMAND_H_
