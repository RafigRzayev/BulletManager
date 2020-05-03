#pragma once

#include "wall.hpp"
#include <vector>

// Generate N random walls which don't overlap
std::vector<Wall> generate_walls(size_t N);