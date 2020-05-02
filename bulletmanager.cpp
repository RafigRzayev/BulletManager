#include "bulletmanager.hpp"
#include <iostream>
#include <cmath>
#include "wall.hpp"
#include "generate_walls.hpp"
#include "algorithm"

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
    static std::vector<Wall> walls = generate_Walls(10);
    auto bullet_it = bullets_.begin();
    while(bullet_it != bullets_.end()) {
        auto position = bullet_it->calculate_position(time);
        switch(position.status) {
            case BULLET_NOT_YET_FLYING : {
                ++bullet_it;
                break;
            }
            case BULLET_IS_FLYING : {
                bullet_it->draw(position.x, position.y);
                auto wall_it = walls.begin();
                while(wall_it != walls.end()) {  
                    switch(wall_it->collision_status(position.x, position.y)) {
                        case NO_COLLISION : {
                            ++wall_it;
                            break;
                        }
                        case HORIZONTAL_REFLECTION: {
                            bullet_it->reflect_horizontally(time, position.x, position.y);
                            wall_it = walls.erase(wall_it);
                            break;
                        }
                        case VERTICAL_REFLECTION: {
                            bullet_it->reflect_vertically(time, position.x, position.y);
                            wall_it = walls.erase(wall_it);
                            break;
                        }
                    }
                }
                ++bullet_it;
                break;
            }
            case BULLET_EXPIRED : {
                bullet_it = bullets_.erase(bullet_it);
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

