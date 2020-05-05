#pragma once

#include "SDL\include\SDL2\SDL.h"
#include <string>

/* Image class loads & stores renderable texture and its dimensions. It uses SDL2 library. 
  Public methods provide interface for drawing texture on the window, and getting texture's dimensions.*/
class Image {
public:
  Image(const std::string& s);
  ~Image();
  void draw(float x, float y) const;
  int get_width() const noexcept;
  int get_height() const noexcept;

private:
  SDL_Texture *image_;
  int width_;
  int height_;
};