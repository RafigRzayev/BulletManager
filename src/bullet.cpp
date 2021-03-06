#include "bullet.hpp"
#include <cmath>
#include <iostream>

Image Bullet::bullet_image_{"bullet.bmp"};

// Default Constructor
Bullet::Bullet() { std::cout << "Bullet Default Constructor\n"; }

// User-Defined Constructor
Bullet::Bullet(float src_x, float src_y, float dst_x, float dst_y, float speed, float time, float life_time)
    : src_x_{src_x}, src_y_{src_y}, time_{time}, life_time_{life_time} {
  std::cout << "Bullet User-Defined Constructor\n";
  assign_x_and_y_speed(dst_x, dst_y, speed);
}

// Copy Constructor
Bullet::Bullet(const Bullet &rhs)
    : src_x_{rhs.src_x_}, src_y_{rhs.src_y_}, speed_x_{rhs.speed_x_},
      speed_y_{rhs.speed_y_}, time_{rhs.time_}, life_time_{rhs.life_time_} {
  std::cout << "Bullet Copy Constructor\n";
}

// Copy Operator
Bullet &Bullet::operator=(const Bullet &rhs) {
  std::cout << "Bullet Copy Operator\n";
  if (this != &rhs) {
    src_x_ = rhs.src_x_;
    src_y_ = rhs.src_y_;
    speed_x_ = rhs.speed_x_;
    speed_y_ = rhs.speed_y_;
    time_ = rhs.time_;
    life_time_ = rhs.life_time_;
  }
  return *this;
}

// Destructor
Bullet::~Bullet() { std::cout << "Bullet Destructor\n"; }

// Calculate bullet position at time t
Bullet_Position Bullet::calculate_position(float current_time) const noexcept {
  if (current_time < time_) {
    return Bullet_Position{0, 0, BULLET_NOT_YET_FLYING};
  } else if (current_time > time_ + life_time_) {
    return Bullet_Position{0, 0, BULLET_EXPIRED};
  } else {
    const float DURATION{current_time - time_};
    const float X = src_x_ + speed_x_ * DURATION;
    const float Y = src_y_ + speed_y_ * DURATION;
    return Bullet_Position{X, Y, BULLET_IS_FLYING};
  }
}

// Render bullet_image_ at given position
void Bullet::draw(float x, float y) const { bullet_image_.draw(x, y); }

// Reverse the speed component. Also update other member variables. 
// Otherwise calculate_position would not work correctly after reflection.
void Bullet::reflect_horizontally(float t, float x, float y) noexcept {
  src_x_ = x;
  src_y_ = y;
  life_time_ -= (t - time_);
  time_ = t;
  speed_x_ = -speed_x_;
}

// Reverse the speed component. Also update other member variables. 
// Otherwise calculate_position would not work correctly after reflection.
void Bullet::reflect_vertically(float t, float x, float y) noexcept {
  src_x_ = x;
  src_y_ = y;
  life_time_ -= (t - time_);
  time_ = t;
  speed_y_ = -speed_y_;
}

// Calculate horizontal and vertical speed components based on speed & destination / source coordinates
void Bullet::assign_x_and_y_speed(float dst_x, float dst_y, float speed) noexcept {
  // Build a triangle from src and dst
  const float X_LENGTH = abs(dst_x - src_x_);
  const float Y_LENGTH = abs(dst_y - src_y_);
  const float HYPOTENUSE = sqrt(X_LENGTH * X_LENGTH + Y_LENGTH * Y_LENGTH);
  if(HYPOTENUSE == 0) {
    speed_x_ = speed_y_ = 0;
    return;
  }
  // Calculate angle
  const float cos_alpha = X_LENGTH / HYPOTENUSE;
  const float sin_alpha = Y_LENGTH / HYPOTENUSE;
  // Use angle to calculate x and y speed components
  speed_x_ = speed * cos_alpha;
  speed_y_ = speed * sin_alpha;

  // Correct speed sign based on direction
  if (src_x_ > dst_x) {
    speed_x_ = -speed_x_;
  }
  if (src_y_ > dst_y) {
    speed_y_ = -speed_y_;
  }
}
