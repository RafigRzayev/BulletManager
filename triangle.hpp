#pragma once

#include <cmath>

// The struct represents a triangle by storing coordinates of 3 vertices of triangle.
struct Triangle {
  float x1_;
  float y1_;
  float x2_;
  float y2_;
  float x3_;
  float y3_;

  // checks if point P[x ,y] is inside the triangle
  bool covers(float x, float y) {
    // Area of current triangle
    float tr_area = calculate_area(x1_, y1_, x2_, y2_, x3_, y3_);
    // Generate 3 triangles by using P and 2 triangle vertices. 
    float sub_tr_1_area = calculate_area(x1_, y1_, x, y, x3_, y3_);
    float sub_tr_2_area = calculate_area(x2_, y2_, x, y, x3_, y3_);
    float sub_tr_3_area = calculate_area(x2_, y2_, x, y, x1_, y1_);
    // P is inside the triangle if sum of 3 areas is equal to triangle area
    float diff = abs(tr_area - (sub_tr_1_area + sub_tr_2_area + sub_tr_3_area));
    return diff < 0.001; // Use this instead of "diff == 0" because of float precision errors
  }

  // calculates area of a triangle
  static float calculate_area(float x1, float y1, float x2, float y2, float x3, float y3) {
    return abs(0.5 * (x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2)));
  }
};