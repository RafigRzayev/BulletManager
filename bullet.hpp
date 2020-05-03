#pragma once

#include "image.hpp"

/* Bullet class description

When BulletManager.Fire(src[x,y], dst[x,y], speed, time, lifetime) is called, we should construct a Bullet object. 
In constructor, we list initialize only some member variables with respective arguments:
1) [src_x_, src_y_]
2) time_
3) life_time_ 

Remaining variables are "destination[x,y]" and "speed". These 3 variables together form notation of bullet direction&speed.
Instead of having these 3 as member variables, we calculate horizontal and vertical speed components in constructor,
and store them as two member variables:
  float speed_x_;
  float speed_y_;

This approach has several benefits:
- We allocate less memory
- Calculation of bullet coordinates at given time becomes very simple
- Effect of collision with walls is easily simulated through changing sign of speed_x_ and speed_y_

Apart from these variables, we also have a shared "bullet_image" object which will be used for rendering.
It stores bullet image, height and width. 

Explanation of methods:
1) calculate_position - reports bullets coordinates at time "t". 
   "t" might be before bullet is fired, or after bullets lifetime. 
   To deal with such cases we return a struct "Bullet_Position" which stores required additional information. 

2) draw - renders "bullet_image" at provided coordinates

3) reflect_horizontally/vertically - reverses appropriate speed component and updates bullet's time, lifetime, and origin 
   accordingly. 

4) calculate_x_and_y_speed - calculates horizontal/vertical speed components according to arguments provided in Fire() method. */

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
  Bullet();
  Bullet(float src_x, float src_y, float dst_x, float dst_y, float speed, float time, float life_time);
  Bullet(const Bullet &rhs);
  Bullet &operator=(const Bullet &rhs);
  ~Bullet();
  Bullet_Position calculate_position(float t);
  void draw(float x, float y);
  void reflect_horizontally(float t, float x, float y);
  void reflect_vertically(float t, float x, float y);

private:
  void calculate_x_and_y_speed(float dst_x, float dst_y, float speed);

  float src_x_{0};
  float src_y_{0};
  float speed_x_{0};
  float speed_y_{0};
  float time_{0};
  float life_time_{0};
  static Image bullet_image_;
};