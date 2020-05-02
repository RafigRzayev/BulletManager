#pragma once

#include "SDL\include\SDL2\SDL.h"
#include <string>
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

    bool inside(float x, float y) {
        float total_area = calculate_area(x1_, y1_, x2_, y2_, x3_, y3_ );
        float a1 = calculate_area(x1_, y1_, x, y, x3_, y3_);
        float a2 = calculate_area(x2_, y2_, x, y, x3_, y3_);
        float a3 = calculate_area(x2_, y2_, x, y, x1_, y1_);
        float diff = abs(total_area - (a1 + a2 + a3));
        return diff < 0.1;
    }
        
};

enum Direction_Change {
    CHANGE_VERTICAL,
    CHANGE_HORIZONTAL,
    NO_COLLISION
};

class Wall {
public:
    // Default Constructor
    Wall();
    // User-Defined Constructor
    Wall(int x, int y);
    // Copy Constructor
    Wall(const Wall&);
    // Copy Operator
    Wall& operator=(const Wall&);
    // Destructor
    ~Wall();
    // Print Wall parameters to console
    void info();
    // Draw Wall on the screen
    void draw();
    int get_x();
    int get_y();
    // checks if drawing a wall at [x,y] will cause an overlap with current wall
    bool coincidies(int x, int y);
    // checks if point is inside the wall;
    bool collision_detected(float x, float y);
    int change_dir(float x, float y);


    static SDL_Texture* WALL_TEXTURE_;
    static const int WALL_WIDTH_;
    static const int WALL_HEIGHT_;
private:
    int x_{0};
    int y_{0};

    static SDL_Texture* load_texture(std::string s);
    static int load_width(std::string s);
    static int load_height(std::string s);
};
