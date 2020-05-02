#include "window.hpp"
#include "gun.hpp"

int main(int argc, char** args) {
    Window& window = Window::getInstance();
    Gun gun;
    SDL_Event e;
    bool quit{false};
    while(!quit) {
        // Process user input
        while(SDL_PollEvent(&e) != 0) {
            quit = window.check_quit(e);
            gun.handle_user_input(e);
        }
        window.clear();
        gun.update_all();
        window.display();
    }
    return 0;
}