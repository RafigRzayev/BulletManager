#pragma once

#include "bulletmanager.hpp"
#include "image.hpp"
#include <chrono>
#include "wall.hpp"
#include <list>

/* Gun class represents a gun which fires bullets.

SDL library is used for reading user keyboard & mouse input

It stores "gun_image" object for rendering the gun.
It stores BulletManager object for handling gun's bullets.

draw() method renders "gun_image" on gun's coordinates

Keyboard input (W/A/S/D keys) affects location of gun:
  - handle_keyboard_input() method reads the pressed keys and sets the gun's speed
  - Update() method changes coordinates of gun according to the current speed and draws it

Mouse click is interpreted as firing a bullet. 
handle_mouse_input() method checks for click event, and fires a bullet with following parameters:
  - bullet source[x, y] = gun's coordinates
  - bullet destination[x, y] = mouse click location
  - bullet speed & life_time = used-defined constants
  - bullet time = return value of current_duration()

current_duration() method reports current game time:
    Firstly, when gun is constructed, we store current system time in the "start_time_" member variable.
    Later in the program, when we call "current_duration" method, it gets current system time and
    calculates the difference with start_time. This value represents the game time.   

handle_use_input() - combines mouse & keyboard input methods for easy public interface
update_all() - combines gun & bulletmanager updates for simple public interface
*/

class Gun {
public:
  Gun(std::list<Wall>* walls);
  ~Gun();
  void handle_user_input(SDL_Event &);
  void update_all();

private:
  void handle_keyboard_input();
  void handle_mouse_input(SDL_Event &);
  void Update();
  float current_duration();
  void draw();

  float gun_x_{0};
  float gun_y_{0};
  float gun_speed_x_{0};
  float gun_speed_y_{0};
  constexpr static const float base_speed_{0.2}; // Adjust for gun movement sensitivity
  BulletManager manager_;
  std::chrono::time_point<std::chrono::system_clock> start_time_;
  static Image gun_image_;
};