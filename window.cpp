#include "window.hpp"

// Window CTOR: Initialize SDL, create SDL_Window and SDL_Renderer
Window::Window() {
    SDL_Init(SDL_INIT_VIDEO);
    window_ = SDL_CreateWindow("Bullet Manager", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, W_WIDTH_, W_HEIGHT_, 0);
    renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
    SDL_SetRenderDrawColor(renderer_, 255, 255, 255, 255);
}

// Window DTOR: Destroy SDL_Window and SDL_Renderer, Close SDL
Window::~Window() {
    SDL_DestroyRenderer(renderer_);
    SDL_DestroyWindow(window_);
    SDL_Quit();
}

void Window::clear() {
    SDL_RenderClear(renderer_);
}

void Window::display() {
    SDL_RenderPresent(renderer_);
}

SDL_Renderer* Window::get_renderer() {
    return renderer_;
}

size_t Window::get_width() const {
    return W_WIDTH_;
}

size_t Window::get_height() const {
    return W_HEIGHT_;
}

bool Window::check_quit(SDL_Event& e) {
    return e.type == SDL_QUIT;
}