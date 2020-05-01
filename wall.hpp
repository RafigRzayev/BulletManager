#pragma once

#include "SDL\include\SDL2\SDL.h"
#include <string>

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
    bool collision_detected(int x, int y);


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
