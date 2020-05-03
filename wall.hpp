#pragma once

#include "image.hpp"

/* Wall class has three member variables:
- [x, y] coordinates of wall's center
- Shared "wall_image" for all Wall objects: wall's image, width, and height.

Explanation of public methods:
1) draw - renders "wall_image" on wall's coordinates

2) coincides - checks if wall located at [x,y] would overlap with current wall.
   Used during random wall generation process to avoid walls rendered on top of each other

3) collision_status - checks if point (bullet) is inside the wall.
   In case of collision, reports how point will be reflected. */

enum Collision_Status {
  NO_COLLISION,
  VERTICAL_REFLECTION,
  HORIZONTAL_REFLECTION
};

class Wall {
public:
  Wall();
  Wall(int x, int y);
  Wall(const Wall &);
  Wall &operator=(const Wall &);
  ~Wall();
  void draw() const;
  bool coincidies(int x, int y) const;
  int collision_status(float x, float y) const;
  static int get_width();
  static int get_height();

private:
  int x_{0};
  int y_{0};
  static Image wall_image_;
};
