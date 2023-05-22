#ifndef CPP3_3VIEWER_V2_0_MODEL_MEMENTO_H_
#define CPP3_3VIEWER_V2_0_MODEL_MEMENTO_H_
#include <vector>

enum class TypeOfChange {
    kMove, kRotate, kScale
};

struct PrevPosition {
    double x;
    double y;
    double z;
    TypeOfChange type;
};

class Memento
{
public:
    Memento(){};
    std::vector<PrevPosition> &get_position() {
        return prev_pos_;
    }

private:
    std::vector<PrevPosition> prev_pos_;
};

#endif // CPP3_3VIEWER_V2_0_MODEL_MEMENTO_H_
