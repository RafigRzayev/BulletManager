#pragma once

#include "SDL\include\SDL2\SDL.h"
#include <string>

/* Image class stores renderable texture and its dimensions. It uses SDL2 library. 
  Public methods provide interface for drawing texture on the window, and getting texture dimensions.*/
class Image {
public:
  Image(const std::string& s);
  ~Image();
  void draw(float x, float y);
  int get_width();
  int get_height();

private:
  SDL_Texture *image_;
  int width_;
  int height_;
};