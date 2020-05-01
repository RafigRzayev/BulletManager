#include "window.hpp"
#include "gun.hpp"
#include "bulletmanager.hpp"
//#include "wall.hpp"
//#include "generate_walls.hpp"

/*void draw_walls(std::vector<Wall>& v) {
    for(size_t i{0}; i < v.size(); ++i) {
        v.at(i).draw();
    }
}*/

int main(int argc, char** args) {
    Window& window = Window::getInstance();
    //std::vector<Wall> walls = generate_Walls(70);
    Gun gun("ufo.bmp");
    SDL_Event e;
    bool quit{false};
    while(!quit) {
        // Process user input
        while(SDL_PollEvent(&e) != 0) {
            if(e.type == SDL_QUIT) {
                quit = true;
            }
            gun.handle_keyboard_input();
            gun.handle_mouse_input(e);
        }
        window.clear();
        gun.move_gun();
        gun.move_bullets();
        window.draw(gun);
        //draw_walls(walls);
        window.display();
    }
    return 0;
}