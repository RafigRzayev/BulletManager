#pragma once

#include "SDL\include\SDL2\SDL.h"

/* Singleton class for creating window & rendering.
Uses SDL library - https://www.libsdl.org

Explanation of public methods:
1) clear - empties the window screen
2) display - draws all rendered content to the screen
3) check_quit - returns true if user presses close button( "X" mark on top-right corner) 
4) get_renderer - enables external users to draw on the window by providing access to the renderer*/

class Window {
public:
  static Window &getInstance() {
    static Window instance;
    return instance;
  }
  ~Window();
  void clear();
  void display();
  bool check_quit(SDL_Event &e) const;
  SDL_Renderer *get_renderer();
  size_t get_width() const;
  size_t get_height() const;
  

  // Disable copy / move semantics for singleton design
  Window(const Window &) = delete;
  Window(Window &&) = delete;
  operator=(const Window &) = delete;
  operator=(Window &&) = delete;

private:
  Window(); // Hide constructor for singleton design

  SDL_Window *window_{nullptr};
  SDL_Renderer *renderer_{nullptr};
  const size_t W_WIDTH_{640};
  const size_t W_HEIGHT_{480};
};