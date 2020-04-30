#include "gun.hpp"
#include "window.hpp"
#include <iostream>

Gun::Gun(std::string s) {
    static Window& window = Window::getInstance();
    SDL_Surface *temp_surface = SDL_LoadBMP(s.c_str());
    gun_width_ = temp_surface->w;
    gun_height_ = temp_surface->h;
    gun_image_ = SDL_CreateTextureFromSurface(window.get_renderer(), temp_surface);
    SDL_FreeSurface(temp_surface);
    // Place gun in the middle of bottom part of screen
    gun_x_ = window.get_width()/2 - gun_width_/2;
    gun_y_ = window.get_height() - gun_height_;

    start_time_ = std::chrono::system_clock::now();
}

Gun::~Gun() {
    SDL_DestroyTexture(gun_image_);
}

SDL_Texture* Gun::get_texture() {
    return gun_image_;
}

float Gun::get_x() const {
    return gun_x_;
}
float Gun::get_y() const {
    return gun_y_;
}

size_t Gun::get_width() const {
    return gun_width_;
}

size_t Gun::get_height() const {
    return gun_height_;
}

void Gun::set_x(size_t new_x) {
    gun_x_ = new_x;
}

void Gun::set_y(size_t new_y) {
    gun_y_ = new_y;
}

void Gun::handle_keyboard_input() {
    // Set vertical movement speed if "W" or "S" keys were pressed
    const unsigned char* keyboard = SDL_GetKeyboardState(NULL);
    if(keyboard[SDL_SCANCODE_W] && !keyboard[SDL_SCANCODE_S]) {
        gun_speed_y_ = -base_speed_;
    } 
    else if(keyboard[SDL_SCANCODE_S] && !keyboard[SDL_SCANCODE_W]) {
        gun_speed_y_ = base_speed_;
    } 
    else {
        gun_speed_y_ = 0;
    }
    // Set horizontal movement speed if "A" or "D" keys were pressed
    if(keyboard[SDL_SCANCODE_A] && !keyboard[SDL_SCANCODE_D]) {
        gun_speed_x_ = -base_speed_;
    } 
    else if(keyboard[SDL_SCANCODE_D] && !keyboard[SDL_SCANCODE_A]) {
        gun_speed_x_ = base_speed_;
    } 
    else {
        gun_speed_x_ = 0;
    }
}

void Gun::handle_mouse_input(SDL_Event& e) {
    if(e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
        int x, y;
        SDL_GetMouseState(&x, &y);
        manager_.Fire(gun_x_ + gun_width_/2, gun_y_ + gun_height_/2, x, y, 100, current_duration(), 20);
    }
}

// Updates gun location according to vertical & horizontal speed
void Gun::move_gun() {
    static Window& window = Window::getInstance();
    gun_x_ += gun_speed_x_;
    gun_y_ += gun_speed_y_;
    // Limit horizontal movement by window borders
    if(gun_x_ < 0 || gun_x_ + gun_width_ > window.get_width()) {
        gun_x_ -= gun_speed_x_;
    }
    // Limit vertical movement for bottom 25% of screen height 
    if(gun_y_ <  window.get_height() * 3.0 / 4  || gun_y_ + gun_height_ > window.get_height()) {
        gun_y_ -= gun_speed_y_;
    }
}

void Gun::move_bullets() {
    manager_.Update(current_duration());
}

float Gun::current_duration() {
    auto current_time = std::chrono::system_clock::now();
    float duration = std::chrono::duration_cast<std::chrono::milliseconds>(current_time - start_time_).count() / 1000.0;
    return duration;
}

