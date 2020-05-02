#include "bulletmanager.hpp"
#include <iostream>
#include <cmath>
#include "wall.hpp"
#include "generate_walls.hpp"

// Default Constructor
BulletManager::BulletManager() {
    std::cout << "BulletManager Default Constructor\n";
}

// Copy Constructor
BulletManager::BulletManager(const BulletManager& rhs) : bullets_{rhs.bullets_} {
    std::cout << "BulletManager Copy Constructor\n";
}

// Move Constructor
BulletManager::BulletManager(BulletManager&& rhs) : bullets_{std::move(rhs.bullets_)} {
    std::cout << "BulletManager Move Constructor\n";
}

// Copy Operator
BulletManager& BulletManager::operator=(const BulletManager& rhs) {
    std::cout << "BulletManager Copy Operator\n";
    if(this != &rhs) {
        bullets_ = rhs.bullets_;
    }
    return *this;
}

// Move Operator
BulletManager& BulletManager::operator=(BulletManager&& rhs) {
    std::cout << "BulletManager Move Operator\n";
    bullets_ = std::move(rhs.bullets_);
    return *this;
}

// Destructor
BulletManager::~BulletManager() {
    std::cout << "BulletManager Destructor\n";
    bullets_.clear();
}

// Calculate bullet location at given time
void BulletManager::Update(float time) {
    static std::vector<Wall> walls = generate_Walls(70);
    const size_t BULLET_COUNT{bullets_.size()};
    for(size_t i{0}; i < BULLET_COUNT; ++i) {
        Bullet& current_bullet = bullets_.at(i);
        auto position = current_bullet.calculate_position(time);
        switch(position.status) {
            case BULLET_NOT_YET_FLYING : {
                break;
            }
            case BULLET_IS_FLYING : {
                current_bullet.draw(position.x, position.y);
                auto it = walls.begin();
                while(it != walls.end()) {
                    if(it->collision_detected(position.x, position.y)) {
                        auto collision_effect = it->change_dir(position.x, position.y);
                        if(collision_effect == CHANGE_HORIZONTAL) {
                            current_bullet.reverse_horizontal_speed(time, position.x, position.y);
                        } else if (collision_effect == CHANGE_VERTICAL) {
                            current_bullet.reverse_vertical_speed(time, position.x, position.y);
                        } else {
                            std::cout << "NO CHANGE MAAAAN!!!!!\n";
                        }
                        it = walls.erase(it);
                    } else {
                        ++it;
                    }
                }
                break;
            }
            case BULLET_EXPIRED : {
                break;
            }
        }
    }
    for(size_t i{0}; i < walls.size(); ++i) {
        walls.at(i).draw();
    }
}

// Add new bullet
void BulletManager::Fire(float src_x, float src_y, float dst_x, float dst_y, float speed, float time, float life_time) {
    std::cout << "BulletManager Fire\n";
    bullets_.emplace_back(src_x, src_y, dst_x, dst_y, speed, time, life_time);
}

// Add n bullets
void BulletManager::fill(size_t n) {
    bullets_.reserve(n);
    for(size_t i{0}; i < n; ++i) {
        Fire(0, 1, 2, 3, 4, 5, 6);
    }
}

// Show internal bullets
void BulletManager::show() {
    const size_t BULLET_COUNT{bullets_.size()};
    if(BULLET_COUNT == 0) {
        std::cout << "Empty\n";
    } else {
        for(size_t i{0}; i < BULLET_COUNT; ++i) {
            bullets_.at(i).info();
        }
    }

}
