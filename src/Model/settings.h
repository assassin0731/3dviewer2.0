#ifndef CPP3_3VIEWER_V2_0_MODEL_SETTINGS_H_
#define CPP3_3VIEWER_V2_0_MODEL_SETTINGS_H_

enum class LineType {kStriple, kUsual};
enum class ProectionType {kCentral, kParallel};
enum class PointType {kNoPoint, kSquare, kCircle};

struct ModelSettings {
    //bool start = false;
    ProectionType proection_type = ProectionType::kParallel;
    float red = 1.0;
    float blue = 1.0;
    float green = 1.0;

    float red_point = 1.0;
    float blue_point = 0.0;
    float green_point = 0.0;

    float red_point_remember = 1.0;
    float blue_point_remember = 0.0;
    float green_point_remember = 0.0;

    float red_bg = 0.0;
    float green_bg = 0.0;
    float blue_bg = 0.0;
    LineType striple_line = LineType::kUsual;
    int line_width = 1;
    int point_size = 0;
    PointType point_type = PointType::kNoPoint;
};



#endif // CPP3_3VIEWER_V2_0_MODEL_SETTINGS_H_
