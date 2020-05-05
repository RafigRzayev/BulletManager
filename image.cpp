#include "image.hpp"
#include "memory"
#include "window.hpp"
#include <iostream>

// User-Defined Constructor - provide name of BMP image to load - e.g. Image("ocean.bmp")
Image::Image(const std::string &s) {
  /*In SDL library, images are loaded into SDL_Surface objects. But SDL_Surface only supports CPU rendering.
  For better performance, we need GPU rendering. So, what we do is: load SDL_Surface, transform it to SDL_Texture, 
  store the texture, and then destroy the surface*/
  std::unique_ptr<SDL_Surface, decltype(&SDL_FreeSurface)> temp_surface(SDL_LoadBMP(s.c_str()), &SDL_FreeSurface);
  auto surface_ptr = temp_surface.get();
  if(surface_ptr == nullptr) {
    std::cout << "Unable to load " << s << std::endl;
    throw;
  }
  // Images for game have been created with white background.
  // Here we set transparency color to white in order to exclude image's background from future rendering
  int status = SDL_SetColorKey( surface_ptr, SDL_TRUE, SDL_MapRGB( surface_ptr->format, 0xFF, 0xFF, 0xFF ) ); 
  if(status < 0) {
    std::cout << "Unable to adjust transparency of " << s << std::endl;
    throw;
  }
  image_ = SDL_CreateTextureFromSurface(Window::getInstance().get_renderer(), surface_ptr);
  if(image_ == nullptr) {
    std::cout << "Unable to create texture from " << s << std::endl;
    throw;
  }
  width_ = surface_ptr->w;
  height_ = surface_ptr->h;
  std::cout << "Image User-Defined Constructor\n";
}

// Destructor
Image::~Image() { 
  SDL_DestroyTexture(image_); 
  std::cout << "Image Destructor\n";
}

// Render image on given coordinates
void Image::draw(float x, float y) const {
  // SDL_Rect stores [x,y] coordintes of top-left corner of texture, and its dimensions
  SDL_Rect rec = {static_cast<int>(x - width_ / 2.0), static_cast<int>(y - height_ / 2.0),
                  static_cast<int>(width_), static_cast<int>(height_)};
  int status = SDL_RenderCopy(Window::getInstance().get_renderer(), image_, NULL, &rec);
  if(status < 0) {
    std::cout << "Exception from SDL_RenderCopy in Image->draw()\n";
    throw;
  }
}

int Image::get_width() const noexcept { return width_; }

int Image::get_height() const noexcept { return height_; }