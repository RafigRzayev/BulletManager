#include "generate_walls.hpp"
#include "window.hpp"
#include <chrono>
#include <random>
#include <iostream>

// Generate N random walls which don't overlap
std::list<Wall> generate_walls(size_t N) {
  std::list<Wall> walls;

  // Define screen and wall dimensions
  Window &window = Window::getInstance();
  const int SCREEN_WIDTH = window.get_width();
  const int SCREEN_HEIGHT = window.get_height();
  const int WALL_WIDTH{Wall::get_width()};
  const int WALL_HEIGHT{Wall::get_height()};

  // Define borders for wall generation (top 3/4 of screen)
  const int LEFT_LIMIT = WALL_WIDTH / 2.0;
  const int RIGHT_LIMIT = SCREEN_WIDTH - (WALL_WIDTH / 2.0);
  const int TOP_LIMIT = WALL_HEIGHT / 2.0 ;
  const int BOT_LIMIT = (SCREEN_HEIGHT * (3.0 / 4.0)) - (WALL_HEIGHT / 2.0);

  // Settings to generate random [x,y] coordinates for the walls
  std::default_random_engine rng{static_cast<long unsigned int>(std::chrono::high_resolution_clock::now().time_since_epoch().count())};
  std::uniform_int_distribution<int> distr_x(LEFT_LIMIT, RIGHT_LIMIT);
  std::uniform_int_distribution<int> distr_y(TOP_LIMIT, BOT_LIMIT);

  auto start_time_ = std::chrono::system_clock::now();
  int TIMEOUT{3};
  for (size_t i{0}; i < N; ++i) {
    // Generate random coordinates for current wall
    int x = distr_x(rng);
    int y = distr_y(rng);
    // Compare for coincidence with previous walls
    auto prev_wall_it = walls.begin();
    while (prev_wall_it != walls.end()) {
      if (prev_wall_it->coincidies(x, y)) {
        // if there is coincidence, generate new coordinates and reset comparison loop
        x = distr_x(rng);
        y = distr_y(rng);
        prev_wall_it = walls.begin();
        if(std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now() - start_time_).count() > TIMEOUT) {
          std::cout << "Timeout in random wall generation. Requested walls don't fit to the screen\n";
          throw;
        }
      } else {
        ++prev_wall_it;
      }
    }
    // Add generated wall to the list
    walls.emplace_back(x, y);
  }
  return walls;
}