#include "graphics/Screen.hpp"
#include "physics/World.hpp"

int main() {
    Screen screen;
    int screenInit = screen.init();
    if (screenInit < 0) {
        return screenInit;
    }

    World world;
    b2Body* player = world.init();

    Camera camera(player);
    screen.setCamera(&camera);

    Uint32 iterationStart;
    bool running = true;
    SDL_Event event;

    while (running) {
        iterationStart = SDL_GetTicks();

        while (SDL_PollEvent(&event)) {
            if (event.window.event == SDL_WINDOWEVENT_CLOSE) {
                running = false;
            }
        }

        screen.displayWorld(&world);
        world.step();

        if (1000.0 / 60 > SDL_GetTicks() - iterationStart) {
            SDL_Delay(1000.0 / 60 - (SDL_GetTicks() - iterationStart));
        }
    }

    return 0;
}