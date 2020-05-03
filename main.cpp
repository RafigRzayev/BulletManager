#include "gun.hpp"
#include "window.hpp"
#include "wall.hpp"
#include "generate_walls.hpp"
#include "vector"

int main(int argc, char **args) {
  Window &window = Window::getInstance();
  const size_t WALL_COUNT_{40};
  std::vector<Wall> walls = generate_walls(WALL_COUNT_);
  Gun gun(&walls);
  SDL_Event e;
  bool quit{false};
  while (!quit) {
    // Process user input
    while (SDL_PollEvent(&e) != 0) {
      quit = window.check_quit(e);
      gun.handle_user_input(e);
    }
    window.clear();
    gun.update_all();
    for(const auto& wall : walls) { wall.draw(); }
    window.display();
  }
  return 0;
}