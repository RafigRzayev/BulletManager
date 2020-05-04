#pragma once

#include "bullet.hpp"
#include "wall.hpp"
#include <list>

class BulletManager {
public:
  BulletManager(std::list<Wall>*);
  BulletManager(const BulletManager &);
  BulletManager(BulletManager &&);
  BulletManager &operator=(const BulletManager &);
  BulletManager &operator=(BulletManager &&);
  ~BulletManager();
  // Calculates bullets' positions & renders them. Removes expired bullets.
  void Update(float time); 
  // Adds new bullet
  void Fire(float src_x, float src_y, float dst_x, float dst_y, float speed,
            float time, float life_time);

private:
  std::list<Bullet> bullets_; // Fired bullets will be added to this list
  std::list<Wall>* walls_; // link to walls under attack, we are not responsible for their memory.
};