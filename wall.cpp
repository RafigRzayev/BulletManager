#include "wall.hpp"
#include <memory>
#include <iostream>
#include "window.hpp"


SDL_Texture* Wall::load_texture(std::string s) {
    std::unique_ptr<SDL_Surface, decltype(&SDL_FreeSurface)>temp_surface(SDL_LoadBMP(s.c_str()), &SDL_FreeSurface);
    return SDL_CreateTextureFromSurface(Window::getInstance().get_renderer(), temp_surface.get());
}

int Wall::load_width(std::string s) {
    std::unique_ptr<SDL_Surface, decltype(&SDL_FreeSurface)>temp_surface(SDL_LoadBMP(s.c_str()), &SDL_FreeSurface);
    return temp_surface->w; 
}

int Wall::load_height(std::string s) {
    std::unique_ptr<SDL_Surface, decltype(&SDL_FreeSurface)>temp_surface(SDL_LoadBMP(s.c_str()), &SDL_FreeSurface);
    return temp_surface->h; 
}

SDL_Texture* Wall::WALL_TEXTURE_{load_texture("wall.bmp")};
const int Wall::WALL_WIDTH_{load_width("wall.bmp")};
const int Wall::WALL_HEIGHT_{load_height("wall.bmp")};

// Default Constructor
Wall::Wall() { 
    std::cout << "Wall Default Constructor\n";
}

// User-Defined Constructor
Wall::Wall(int x, int y) : x_{x}, y_{y} { 
    std::cout << "Wall User-Defined Constructor\n";
}

// Copy Constructor
Wall::Wall(const Wall& rhs) : x_{rhs.x_}, y_{rhs.y_} {
    std::cout << "Wall Copy Constructor\n";
}

// Copy Operator
Wall& Wall::operator=(const Wall& rhs) {
    std::cout << "Wall Copy Operator\n";
    if(this != &rhs) {
        x_ = rhs.x_;
        y_ = rhs.y_;
    }
    return *this;
} 

// Destructor
Wall::~Wall() {
    std::cout << "Wall Destructor\n";
}

// Print Wall parameters to console
void Wall::info() {
    std::cout << "[ " << x_ << ", " << y_ << ", " << WALL_WIDTH_ << ", " << WALL_HEIGHT_ << " ]\n";
}

// Draw Wall on the screen
void Wall::draw() {
    SDL_Rect rec = {
        static_cast<int>(x_ - WALL_WIDTH_/2), static_cast<int>(y_ - WALL_HEIGHT_/2),
        static_cast<int>(WALL_WIDTH_), static_cast<int>(WALL_HEIGHT_) };
    SDL_RenderCopy(Window::getInstance().get_renderer(), WALL_TEXTURE_, NULL, &rec);    
}


int Wall::get_x() {
    return x_;
}

int Wall::get_y() {
    return y_;
}

bool Wall::coincidies(int x, int y) {
    return (x >= x_ - WALL_WIDTH_ ) && (x <= x_ + WALL_WIDTH_) && (y >= y_ - WALL_HEIGHT_) && (y <= y_ + WALL_HEIGHT_);
}

bool Wall::collision_detected(float x, float y) {
    return (x >= x_ - WALL_WIDTH_/2 ) && (x <= x_ + WALL_WIDTH_/2) && (y >= y_ - WALL_HEIGHT_/2) && (y <= y_ + WALL_HEIGHT_/2);
}

int Wall::change_dir(float x, float y) {
    float X_LEFT = x_ - (WALL_WIDTH_ / 2.0);
    float X_RIGHT = x_ + (WALL_WIDTH_ / 2.0);
    float Y_TOP = y_ - (WALL_HEIGHT_ / 2.0);
    float Y_BOT = y_ + (WALL_HEIGHT_ / 2.0);
    Triangle TOP = {X_LEFT, Y_TOP, static_cast<float>(x_), static_cast<float>(y_), X_RIGHT, Y_TOP};
    Triangle BOT = {X_LEFT, Y_BOT, static_cast<float>(x_), static_cast<float>(y_), X_RIGHT, Y_BOT};
    Triangle LEFT = {X_LEFT, Y_TOP, static_cast<float>(x_), static_cast<float>(y_), X_LEFT, Y_BOT};
    Triangle RIGHT = {X_RIGHT, Y_TOP, static_cast<float>(x_), static_cast<float>(y_), X_RIGHT, Y_BOT};
    if(TOP.inside(x, y) || BOT.inside(x, y)) {
        return CHANGE_VERTICAL;
    } else if (LEFT.inside(x, y) || RIGHT.inside(x, y)) {
        return CHANGE_HORIZONTAL;
    }
    else {
        return NO_COLLISION;
    }
}