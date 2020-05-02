#include "window.hpp"
#include "gun.hpp"
#include "bulletmanager.hpp"



int main(int argc, char** args) {
    Window& window = Window::getInstance();
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
        window.display();
    }
    return 0;
}