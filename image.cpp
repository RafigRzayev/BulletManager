#include "image.hpp"
#include "memory"
#include "window.hpp"

// User-Defined Constructor - provide name of BMP image to load
Image::Image(const std::string &s) {
  // In SDL library images are loaded into SDL_Surface objects. But SDL_Surface
  // only supports CPU rendering. For better performance, we need GPU rendering.
  // Thus, SDL_Texture object is required. So, we have to transform SDL_Surface
  // to SDL_Texture, store SDL_Texture as member variable and then destroy SDL_Surface
  std::unique_ptr<SDL_Surface, decltype(&SDL_FreeSurface)> temp_surface(SDL_LoadBMP(s.c_str()), &SDL_FreeSurface);
  image_ = SDL_CreateTextureFromSurface(Window::getInstance().get_renderer(), temp_surface.get());
  width_ = temp_surface.get()->w;
  height_ = temp_surface.get()->h;
}

// Destructor
Image::~Image() { SDL_DestroyTexture(image_); }

// Render image on given coordinates
void Image::draw(float x, float y) {
  // SDL_Rect stores [x,y] coordintes of top_left corner of the texture, and texture dimensions
  SDL_Rect rec = {static_cast<int>(x - width_ / 2.0), static_cast<int>(y - height_ / 2.0),
                  static_cast<int>(width_), static_cast<int>(height_)};
  SDL_RenderCopy(Window::getInstance().get_renderer(), image_, NULL, &rec);
}

int Image::get_width() { return width_; }

int Image::get_height() { return height_; }