#include "bullet.hpp"
#include <cmath>
#include <memory>
#include "window.hpp"

SDL_Texture* Bullet::load_texture(std::string s) {
    std::unique_ptr<SDL_Surface, decltype(&SDL_FreeSurface)> temp_surface(SDL_LoadBMP(s.c_str()), &SDL_FreeSurface);
    return SDL_CreateTextureFromSurface(Window::getInstance().get_renderer(), temp_surface.get());
}

size_t Bullet::load_texture_width(std::string s) {
    std::unique_ptr<SDL_Surface, decltype(&SDL_FreeSurface)> temp_surface(SDL_LoadBMP(s.c_str()), &SDL_FreeSurface);
    return temp_surface->w;    
}

size_t Bullet::load_texture_height(std::string s) {
    std::unique_ptr<SDL_Surface, decltype(&SDL_FreeSurface)> temp_surface(SDL_LoadBMP(s.c_str()), &SDL_FreeSurface);
    return temp_surface->h;    
}

SDL_Texture* Bullet::BULLET_TEXTURE_{load_texture("bullet.bmp")};
const size_t Bullet::BULLET_WIDTH_{load_texture_width("bullet.bmp")};
const size_t Bullet::BULLET_HEIGHT_{load_texture_height("bullet.bmp")};

// Default Constructor
Bullet::Bullet() {
    std::cout << "Bullet Default Constructor\n";
}

// User-Defined Constructor
Bullet::Bullet(float src_x, float src_y, float dst_x, float dst_y, float speed, float time, float life_time) : 
    src_x_{src_x}, src_y_{src_y}, time_{time}, life_time_{life_time}  {
    std::cout << "Bullet User-Defined Constructor\n";
    calculate_x_and_y_speed(dst_x, dst_y, speed);
}

// Copy Constructor
Bullet::Bullet(const Bullet& rhs) : 
    src_x_{rhs.src_x_}, src_y_{rhs.src_y_}, speed_x_{rhs.speed_x_}, speed_y_{rhs.speed_y_}, time_{rhs.time_}, life_time_{rhs.life_time_} {
        std::cout << "Bullet Copy Constructor\n";        
}

// Copy Operator
Bullet& Bullet::operator=(const Bullet& rhs) {
    std::cout <<"Bullet Copy Operator\n";     
    if(this != &rhs) {
        src_x_ = rhs.src_x_;
        src_y_ = rhs.src_y_;
        speed_x_ = rhs.speed_x_;
        speed_y_ = rhs.speed_y_;
        time_ = rhs.time_;
        life_time_ = rhs.life_time_;
    }
    return *this;
}

// Destructor
Bullet::~Bullet() {
    std::cout << "Bullet Destructor\n";
}

// Print bullet parameters to console
void Bullet::info() {
    std::cout << "[" << src_x_ << ", " << src_y_ << ", " << speed_x_ << ", " << speed_y_ << ", " << time_ << ", " << life_time_ << "]\n"; 
}

// Calculate bullet position at time t
Bullet_Position Bullet::calculate_position(float current_time) {
    if(current_time < time_) {
        return Bullet_Position{0, 0, BULLET_NOT_YET_FLYING};
    } 
    else if(current_time > time_ + life_time_) {
        return Bullet_Position{0, 0, BULLET_EXPIRED};
    } 
    else {
        const float DURATION{current_time - time_};
        const float X = src_x_ + speed_x_ * DURATION;
        const float Y = src_y_ + speed_y_ * DURATION;
        return Bullet_Position{X, Y, BULLET_IS_FLYING};
    }    
}

void Bullet::draw(float x, float y) {
    SDL_Rect rec = {
        static_cast<int>(x - BULLET_WIDTH_/2), static_cast<int>(y - BULLET_HEIGHT_/2),
        static_cast<int>(BULLET_WIDTH_), static_cast<int>(BULLET_HEIGHT_) };
    SDL_RenderCopy(Window::getInstance().get_renderer(), BULLET_TEXTURE_, NULL, &rec);    
}

// Calculate horizontal and vertical speed based on speed & destination/ source coordinates
void Bullet::calculate_x_and_y_speed(float dst_x, float dst_y, float speed) {
    const float X_LENGTH = abs(dst_x - src_x_);
    const float Y_LENGTH = abs(dst_y - src_y_);
    const float HYPOTENUSE = sqrt(X_LENGTH * X_LENGTH + Y_LENGTH * Y_LENGTH);

    const float cos_alpha = X_LENGTH / HYPOTENUSE;
    const float sin_alpha = Y_LENGTH / HYPOTENUSE;

    speed_x_ = speed * cos_alpha;
    speed_y_ = speed * sin_alpha;

    // Correct speed sign based on direction
    if(src_x_ > dst_x) {
        speed_x_ = -speed_x_;
    }
    if(src_y_ > dst_y) {
        speed_y_ = -speed_y_;
    }
}
