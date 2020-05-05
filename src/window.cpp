#include "window.hpp"
#include <iostream>

// Window Constructor - Initialize SDL, create window, create & adjust renderer
Window::Window() {
  if(SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cout << "SDL_Init error\n";
    throw;
  }
  window_ = SDL_CreateWindow("Bullet Manager", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, W_WIDTH_, W_HEIGHT_, 0);
  if(window_ == nullptr) {
    std::cout << "SDL_CreateWindow error\n";
    throw;
  }
  // use GPU renderer
  renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED); 
  if(renderer_ == nullptr) {
    std::cout << "SDL_CreateRenderer error\n";
    throw;
  }
  SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
  // Set color for clearing the screen
  if(SDL_SetRenderDrawColor(renderer_, 255, 255, 255, 255) < 0) {
    std::cout << "SDL_SetRenderDrawColor error\n";
    throw;
  }
  std::cout << "Window Constructor\n";
}

// Window Destructor
Window::~Window() {
  SDL_DestroyRenderer(renderer_);
  SDL_DestroyWindow(window_);
  SDL_Quit();
  std::cout << "Window Destructor\n";
}

// Clear the window screen
void Window::clear() { 
  if(SDL_RenderClear(renderer_) < 0) {
    std::cout << "SDL_RenderClear error\n";
    throw;
  }
}

// Show rendered content on the window screen
void Window::display() { SDL_RenderPresent(renderer_); }

// Check if user pressed window close button
bool Window::check_quit(SDL_Event &e) const noexcept { return e.type == SDL_QUIT; }

// Provide renderer so that external users can draw on the window
SDL_Renderer *Window::get_renderer() noexcept { return renderer_; }

size_t Window::get_width() const noexcept { return W_WIDTH_; }

size_t Window::get_height() const noexcept { return W_HEIGHT_; }

