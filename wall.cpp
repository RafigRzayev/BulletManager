#include "wall.hpp"
#include <iostream>

Image Wall::wall_image_{"wall.bmp"};

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
    std::cout << "[ " << x_ << ", " << y_ << ", " << wall_image_.get_width() << ", " << wall_image_.get_height() << " ]\n";
}

// Draw Wall on the screen
void Wall::draw() {
    wall_image_.draw(x_, y_);    
}


int Wall::get_x() {
    return x_;
}

int Wall::get_y() {
    return y_;
}

bool Wall::coincidies(int x, int y) {
    return (x >= x_ - wall_image_.get_width() ) && (x <= x_ + wall_image_.get_width()) && (y >= y_ - wall_image_.get_height()) && (y <= y_ + wall_image_.get_height());
}

int Wall::collision_status(float x, float y) {
    // Borders of the wall
    float LEFT_BORDER_X = x_ - (wall_image_.get_width() / 2.0);
    float RIGHT_BORDER_X = x_ + (wall_image_.get_width() / 2.0);
    float TOP_BORDER_Y = y_ - (wall_image_.get_height() / 2.0);
    float BOT_BORDER_Y = y_ + (wall_image_.get_height() / 2.0);
    // Check if there is collision (origin of SDL coordinate system is top-left corner of window)
    if( x >= LEFT_BORDER_X && x <= RIGHT_BORDER_X && y >= TOP_BORDER_Y && y <= BOT_BORDER_Y) {
        // This part calculates direction of reflection 
        // Divide wall into 4 triangles. Check in which triangle is bullet.
        // If it is inside top or bottom triangle, vertical speed will be reversed, and horizontal speed won't change.
        // Similarly, if it falls inside left/right triangle, then only horizontal speed will change direction.
        Triangle TOP_TRIANGLE = {LEFT_BORDER_X, TOP_BORDER_Y, static_cast<float>(x_), static_cast<float>(y_), RIGHT_BORDER_X, TOP_BORDER_Y};
        Triangle BOT_TRIANGLE = {LEFT_BORDER_X, BOT_BORDER_Y, static_cast<float>(x_), static_cast<float>(y_), RIGHT_BORDER_X, BOT_BORDER_Y};
        if(TOP_TRIANGLE.covers(x, y) || BOT_TRIANGLE.covers(x, y)) {
            return VERTICAL_REFLECTION;
        } else {
            return HORIZONTAL_REFLECTION;
        }       
    } else {
        return NO_COLLISION;
    }
}