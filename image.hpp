#pragma once

#include "SDL\include\SDL2\SDL.h"
#include <string>

class Image {
public:
    Image(std::string s);
    ~Image();
    void draw(float x, float y);
    int get_width();
    int get_height();
private:
    SDL_Texture* image_;
    int width_;
    int height_;
};