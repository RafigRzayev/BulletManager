#include "image.hpp"
#include "window.hpp"
#include "memory"

Image::Image(std::string s) {
    std::unique_ptr<SDL_Surface, decltype(&SDL_FreeSurface)>temp_surface(SDL_LoadBMP(s.c_str()), &SDL_FreeSurface);
    image_ = SDL_CreateTextureFromSurface(Window::getInstance().get_renderer(), temp_surface.get());
    width_ = temp_surface.get()->w;
    height_ = temp_surface.get()->h;
}

Image::~Image() {
    SDL_DestroyTexture(image_);
}

void Image::draw(float x, float y) {
    SDL_Rect rec = {
        static_cast<int>(x - width_/2), static_cast<int>(y - height_/2),
        static_cast<int>(width_), static_cast<int>(height_) };
    SDL_RenderCopy(Window::getInstance().get_renderer(), image_, NULL, &rec);       
}

int Image::get_width() {
    return width_;
}

int Image::get_height() {
    return height_;
}