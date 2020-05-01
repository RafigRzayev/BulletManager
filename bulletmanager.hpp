#pragma once

#include "bullet.hpp"
#include <vector>

class BulletManager {
public: 
    // Default Constructor
    BulletManager();
    // Copy Constructor
    BulletManager(const BulletManager&);
    // Move Constructor
    BulletManager(BulletManager&&);
    // Copy Operator
    BulletManager& operator=(const BulletManager&);
    // Move Operator
    BulletManager& operator=(BulletManager&&);
    //Destructor
    ~BulletManager();
    // Calculate bullet location at given time
    void Update(float time);
    // Add new bullet
    void Fire(float src_x, float src_y, float dst_x, float dst_y, float speed, float time, float life_time);
    // Add n bullets
    void fill(size_t n);
    // Show internal bullets
    void show();
private:
    std::vector<Bullet> bullets_;


};