#include "window.hpp"

// Window Constructor - Initialize SDL, create window, create & adjust renderer
Window::Window() {
  SDL_Init(SDL_INIT_VIDEO);
  window_ = SDL_CreateWindow("Bullet Manager", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, W_WIDTH_, W_HEIGHT_, 0);
  renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED); // use GPU rendering
  SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
  SDL_SetRenderDrawColor(renderer_, 255, 255, 255, 255); // Set color for clearing the screen
}

// Window Destructor
Window::~Window() {
  SDL_DestroyRenderer(renderer_);
  SDL_DestroyWindow(window_);
  SDL_Quit();
}

// Clear the window screen
void Window::clear() { SDL_RenderClear(renderer_); }

// Show rendered content on the window screen
void Window::display() { SDL_RenderPresent(renderer_); }

// Check if user pressed window close button
bool Window::check_quit(SDL_Event &e) const { return e.type == SDL_QUIT; }

// Provide renderer so that external users can draw on the window
SDL_Renderer *Window::get_renderer() { return renderer_; }

size_t Window::get_width() const { return W_WIDTH_; }

size_t Window::get_height() const { return W_HEIGHT_; }

