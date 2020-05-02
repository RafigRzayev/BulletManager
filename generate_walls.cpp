#include "generate_walls.hpp"
#include <chrono>
#include <random>
#include "window.hpp"

std::vector<Wall> generate_Walls(size_t N) {
    std::vector<Wall> walls;
    walls.reserve(N);

    Window &window = Window::getInstance();
    const int SCREEN_WIDTH =window.get_width();
    const int SCREEN_HEIGHT =window.get_height();
    const int WALL_WIDTH{ Wall::wall_image_.get_width()};
    const int WALL_HEIGHT{ Wall::wall_image_.get_height()};

    const int LEFT_LIMIT = WALL_WIDTH / 2.0 ;
    const int RIGHT_LIMIT = SCREEN_WIDTH - (WALL_WIDTH  / 2.0) ;
    const int TOP_LIMIT = WALL_HEIGHT / 2 ;
    const int BOT_LIMIT = (SCREEN_HEIGHT * (3.0 / 4.0)) - (WALL_HEIGHT / 2) ;

    std::default_random_engine rng{static_cast<long unsigned int>(std::chrono::high_resolution_clock::now().time_since_epoch().count())};
    std::uniform_int_distribution<int> distr_x(LEFT_LIMIT, RIGHT_LIMIT);
    std::uniform_int_distribution<int> distr_y(TOP_LIMIT, BOT_LIMIT);

    // Generate N walls
    for(size_t i{0}; i < N; ++i) {
        // Generate random coordinates for current wall
        int x = distr_x(rng);
        int y = distr_y(rng);
        // Compare for coincidence with previous walls
        for(size_t j{0}; j < i; ++j) {
            if(walls.at(j).coincidies(x, y)) { 
                // if there is coincidence, generate new coordinates and reset comparison loop
                x = distr_x(rng);
                y = distr_y(rng);
                j = -1;
            }
        }
        walls.emplace_back(x, y);
    }   
    return walls;
}