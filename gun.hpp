#pragma once 

#include "bulletmanager.hpp"
#include <chrono>
#include "image.hpp"

class Gun {
public:
    Gun();
    ~Gun();
    void handle_user_input(SDL_Event&);
    void update_all();

private:
    void Update();
    float current_duration();
    void draw();
    void handle_keyboard_input();
    void handle_mouse_input(SDL_Event&);
    float gun_x_{0};
    float gun_y_{0};    
    float gun_speed_x_{0};
    float gun_speed_y_{0};
    constexpr static const float base_speed_{0.2};
    BulletManager manager_{};
    std::chrono::time_point<std::chrono::system_clock> start_time_;
    static Image gun_image_;
};