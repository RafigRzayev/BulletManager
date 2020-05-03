#pragma once

#include <cmath>

struct Triangle {
    float x1_;
    float y1_;
    float x2_;
    float y2_;
    float x3_;
    float y3_;

    float calculate_area(float x1, float y1, float x2, float y2, float x3, float y3) {
        return abs(0.5 * ( x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2)));
    }

    bool covers(float x, float y) {
        float total_area = calculate_area(x1_, y1_, x2_, y2_, x3_, y3_ );
        float a1 = calculate_area(x1_, y1_, x, y, x3_, y3_);
        float a2 = calculate_area(x2_, y2_, x, y, x3_, y3_);
        float a3 = calculate_area(x2_, y2_, x, y, x1_, y1_);
        float diff = abs(total_area - (a1 + a2 + a3));
        return diff < 0.1;
    }        
};