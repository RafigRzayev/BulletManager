#pragma once

#include "bullet.hpp"
#include <vector>

class BulletManager {
public:
  BulletManager();
  BulletManager(const BulletManager &);
  BulletManager(BulletManager &&);
  BulletManager &operator=(const BulletManager &);
  BulletManager &operator=(BulletManager &&);
  ~BulletManager();
  // Calculates bullets' positions & renders them
  void Update(float time); 
  // Adds new bullet
  void Fire(float src_x, float src_y, float dst_x, float dst_y, float speed,
            float time, float life_time);

private:
  std::vector<Bullet> bullets_;
};