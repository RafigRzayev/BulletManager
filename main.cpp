#include "window.hpp"
#include "gun.hpp"
#include "bulletmanager.hpp"

int main(int argc, char** args) {
    // Testing
    {
        BulletManager manager;
        manager.Fire(10, 15, 20, 27, 30, 40, 10);
        BulletManager manager2(std::move(manager));
        manager.show();
        manager2.show();
    }
  
    Window& window = Window::getInstance();
    Gun gun("ufo.bmp");
    SDL_Event e;
    bool quit{false};
    while(!quit) {
        while(SDL_PollEvent(&e) != 0) {
            if(e.type == SDL_QUIT) {
                quit = true;
            }
            gun.handle_keyboard_input();
        }
        window.clear();
        gun.move();
        window.draw(gun);
        window.display();
    }
    return 0;
}