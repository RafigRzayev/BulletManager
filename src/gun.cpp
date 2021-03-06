#include "gun.hpp"
#include "window.hpp"
#include <iostream>

Image Gun::gun_image_{"ufo.bmp"};

// Constructor
Gun::Gun(std::list<Wall>* walls) : manager_{walls} { // links bullet manager to the relevant walls
  std::cout << "Gun Constructor\n";
  static Window &window = Window::getInstance();
  // Place gun in the bottom of window
  gun_x_ = window.get_width() / 2.0;
  gun_y_ = window.get_height() - gun_image_.get_height();
  // calculate game start time. 
  start_time_ = std::chrono::system_clock::now();
}

// Destructor
Gun::~Gun() { std::cout << "Gun Destructor\n"; } 

// Adjust gun speed and fire bullets according to user input
void Gun::handle_user_input(SDL_Event &e) {
  handle_keyboard_input();
  handle_mouse_input(e);
}

void Gun::handle_keyboard_input() {
  // Set vertical movement speed if "W" or "S" keys were pressed
  const unsigned char *keyboard = SDL_GetKeyboardState(NULL);
  if(keyboard == nullptr) {
    std::cout << "SDL_GetKeyboardState error\n";
    throw;
  }
  if (keyboard[SDL_SCANCODE_W] && !keyboard[SDL_SCANCODE_S]) {
    gun_speed_y_ = -base_speed_;
  } else if (keyboard[SDL_SCANCODE_S] && !keyboard[SDL_SCANCODE_W]) {
    gun_speed_y_ = base_speed_;
  } else {
    gun_speed_y_ = 0;
  }
  // Set horizontal movement speed if "A" or "D" keys were pressed
  if (keyboard[SDL_SCANCODE_A] && !keyboard[SDL_SCANCODE_D]) {
    gun_speed_x_ = -base_speed_;
  } else if (keyboard[SDL_SCANCODE_D] && !keyboard[SDL_SCANCODE_A]) {
    gun_speed_x_ = base_speed_;
  } else {
    gun_speed_x_ = 0;
  }
}

// refer to header for explanation
void Gun::handle_mouse_input(SDL_Event &e) {
  if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
    int x, y;
    SDL_GetMouseState(&x, &y);
    manager_.Fire(gun_x_, gun_y_, x, y, 150, current_duration(), 15);
  }
}

void Gun::update_all() {
  // Updates & Renders bullets
  manager_.Update(current_duration()); 
  // Upadates & renders the gun
  Update();
}

// Updates gun location according to vertical & horizontal speed. Then renders it at new location
void Gun::Update() {
  static Window &window = Window::getInstance();
  gun_x_ += gun_speed_x_;
  gun_y_ += gun_speed_y_;
  // Limit horizontal movement by window borders
  if (gun_x_ - gun_image_.get_width() / 2.0 < 0 ||
      gun_x_ + gun_image_.get_width() / 2.0 > window.get_width()) {
    gun_x_ -= gun_speed_x_;
  }
  // Limit vertical movement for bottom 25% of screen height
  if (gun_y_ - gun_image_.get_height() / 2.0 < window.get_height() * 3.0 / 4.0 ||
      gun_y_ + gun_image_.get_height() / 2.0 > window.get_height()) {
    gun_y_ -= gun_speed_y_;
  }
  draw();
}

// Get current game time
float Gun::current_duration() {
  auto current_time = std::chrono::system_clock::now();
  float duration = std::chrono::duration_cast<std::chrono::milliseconds>(current_time - start_time_).count() / 1000.0;
  return duration;
}

// Render gun on its current coordinates
void Gun::draw() { gun_image_.draw(gun_x_, gun_y_); }
