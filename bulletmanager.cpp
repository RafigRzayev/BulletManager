#include "bulletmanager.hpp"
#include <iostream>

// User-Defined Constructor
BulletManager::BulletManager(std::list<Wall> *walls) : walls_{walls} {
  std::cout << "BulletManager Default Constructor\n";
}

// Copy Constructor
BulletManager::BulletManager(const BulletManager &rhs)
    : bullets_{rhs.bullets_}, walls_{rhs.walls_} {
  std::cout << "BulletManager Copy Constructor\n";
}

// Move Constructor
BulletManager::BulletManager(BulletManager &&rhs)
    : bullets_{std::move(rhs.bullets_)}, walls_{rhs.walls_} {
  std::cout << "BulletManager Move Constructor\n";
  rhs.walls_ = nullptr;
}

// Copy Operator
BulletManager &BulletManager::operator=(const BulletManager &rhs) {
  std::cout << "BulletManager Copy Operator\n";
  if (this != &rhs) {
    bullets_ = rhs.bullets_;
    walls_ = rhs.walls_;
  }
  return *this;
}

// Move Operator
BulletManager &BulletManager::operator=(BulletManager &&rhs) {
  std::cout << "BulletManager Move Operator\n";
  bullets_ = std::move(rhs.bullets_);
  walls_ = rhs.walls_;
  rhs.walls_ = nullptr;
  return *this;
}

// Destructor
BulletManager::~BulletManager() {
  std::cout << "BulletManager Destructor\n";
  bullets_.clear();
}

/* Explanation of Update algorithm:
  Iterate through all bullets and call bullet.calculate_position() method
  On each iteration check:
  - If bullet is not yet fired, continue the loop
  - If bullet is expired, destroy the bullet and then continue
  - If bullet is flying, then:
      1) Iterate through all walls, check if bullet collides with any wall
          - If it collides, destroy the wall and reflect the bullet
      2) Render the bullet at calculated coordinates */
void BulletManager::Update(float time) {
  if(walls_ == nullptr) {
    std::cout << "Walls linked to bulletmanger are nullptr\n";
    throw;
  }
  auto bullet_it = bullets_.begin();
  while (bullet_it != bullets_.end()) {
    auto position = bullet_it->calculate_position(time);
    switch (position.status) {
      case BULLET_NOT_YET_FLYING: {
        ++bullet_it;
        break;
      }
      case BULLET_IS_FLYING: {
        bullet_it->draw(position.x, position.y);
        auto wall_it = walls_->begin();
        while (wall_it != walls_->end()) {
          switch (wall_it->collision_status(position.x, position.y)) {
            case NO_COLLISION: {
              ++wall_it;
              break;
            }
            case HORIZONTAL_REFLECTION: {
              bullet_it->reflect_horizontally(time, position.x, position.y);
              wall_it = walls_->erase(wall_it);
              break;
            }
            case VERTICAL_REFLECTION: {
              bullet_it->reflect_vertically(time, position.x, position.y);
              wall_it = walls_->erase(wall_it);
              break;
            }
          }
        }
        ++bullet_it;
        break;
      }
      case BULLET_EXPIRED: {
        bullet_it = bullets_.erase(bullet_it);
        break;
      }
    }
  }
}

// Add new bullet
void BulletManager::Fire(float src_x, float src_y, float dst_x, float dst_y,
                         float speed, float time, float life_time) {
  std::cout << "BulletManager Fire\n";
  bullets_.emplace_back(src_x, src_y, dst_x, dst_y, speed, time, life_time);
}
