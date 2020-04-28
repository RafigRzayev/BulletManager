#pragma once 

#include "SDL\include\SDL2\SDL.h"
#include <string>

class Gun {
public:
Gun(std::string s);
~Gun();
SDL_Texture* get_texture();
float get_x() const ;
float get_y() const;
size_t get_width() const;
size_t get_height() const;
void set_x(size_t);
void set_y(size_t);
void handle_keyboard_input();
void move();

private:
size_t gun_width_{0};
size_t gun_height_{0};
float gun_x_{0};
float gun_y_{0};
float gun_speed_x_{0};
float gun_speed_y_{0};
constexpr static const float base_speed_{0.2};


SDL_Texture* gun_image_{nullptr};
};