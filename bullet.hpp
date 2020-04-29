#pragma once

#include <iostream>

class Bullet {
public:
    // Default Constructor
    Bullet();
    // User-Defined Constructor
    Bullet(float src_x, float src_y, float dst_x, float dst_y, float speed, float time, float life_time);
    // Copy Constructor
    Bullet(const Bullet& rhs);
    // Copy Operator
    Bullet& operator=(const Bullet& rhs);
    // Destructor
    ~Bullet();
    // Print bullet parameters to console
    void info();
    // Calculate horizontal and vertical speed based on speed & destination/ source coordinates
    void calculate_x_and_y_speed(float dst_x, float dst_y, float speed);

    float src_x_{0};
    float src_y_{0};
    float speed_x_{0};
    float speed_y_{0};
    float time_{0};
    float life_time_{0};
};