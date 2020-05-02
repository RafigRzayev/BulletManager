#pragma once

#include "image.hpp"

struct Bullet_Position {
    float x;
    float y;
    int status;
};

enum Bullet_Life_Flags {
    BULLET_NOT_YET_FLYING,
    BULLET_IS_FLYING,
    BULLET_EXPIRED
};

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
    // Calculate bullet position at time t
    Bullet_Position calculate_position(float t);
    // Draw Bullet on the screen
    void draw(float x, float y);
    void reflect_horizontally(float t, float x, float y);
    void reflect_vertically(float t, float x, float y);

private:
    // Calculate horizontal and vertical speed based on speed & destination/ source coordinates
    void calculate_x_and_y_speed(float dst_x, float dst_y, float speed);

    float src_x_{0};
    float src_y_{0};
    float speed_x_{0};
    float speed_y_{0};
    float time_{0};
    float life_time_{0};
    static Image bullet_image_;
};