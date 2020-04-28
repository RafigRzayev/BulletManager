#pragma once

#include "SDL\include\SDL2\SDL.h"
#include "gun.hpp"

// Grahpics class for creating window & rendering
class Window {
public:
    static Window& getInstance() {
        static Window instance;
        return instance;
    }
    ~Window();
    void clear();
    void draw(Gun&);
    void display();
    SDL_Renderer* get_renderer();
    size_t get_width() const;
    size_t get_height() const;
    
// Disable copy / move semantics
Window(const Window&) = delete;
Window(Window&&) = delete;
operator=(const Window&) = delete;
operator=(Window&&) = delete;

private:   
Window();
SDL_Window *window_{nullptr};
SDL_Renderer *renderer_{nullptr};
const size_t W_WIDTH_{640};
const size_t W_HEIGHT_{480};
bool state{false};
};