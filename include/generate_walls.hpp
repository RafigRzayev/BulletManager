#pragma once

#include "wall.hpp"
#include <list>

// Generate N random walls which don't overlap
std::list<Wall> generate_walls(size_t N);