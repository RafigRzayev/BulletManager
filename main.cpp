#include "window.hpp"
#include "gun.hpp"
#include "bulletmanager.hpp"

int main(int argc, char** args) {
    Window& window = Window::getInstance();
    Gun gun("ufo.bmp");
    SDL_Event e;
    bool quit{false};
    while(!quit) {
        // User input part
        while(SDL_PollEvent(&e) != 0) {
            // Press x to close program
            if(e.type == SDL_QUIT) {
                quit = true;
            }
            // Get keyboard input for gun movement
            gun.handle_keyboard_input();
            // Get mouse input to fire bullets
            gun.handle_mouse_input(e);
        }
        window.clear();
        // Update gun location based on keyboard input
        gun.move_gun();
        // Update bullet location
        gun.move_bullets();
        // Draw gun at new location
        window.draw(gun);
        // Display new content
        window.display();
    }
    return 0;
}