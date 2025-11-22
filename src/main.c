#include <SDL2/SDL.h>
#include "physics.h"
#include "render.h"

int main() {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *win = SDL_CreateWindow("Cinematic Pendulum",
                                       SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED,
                                       900, 700, 0);

    SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

    Simulation sim;
    sim.dt = 0.016;
    sim.mode = 0;
    init_single(&sim);
    init_double(&sim);

    double zoom = 1.0;

    int running = 1;
    while (running) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT)
                running = 0;

            if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_1) sim.mode = 0;
                if (e.key.keysym.sym == SDLK_2) sim.mode = 1;
                if (e.key.keysym.sym == SDLK_EQUALS) zoom *= 1.05;
                if (e.key.keysym.sym == SDLK_MINUS) zoom *= 0.95;
            }

            if (e.type == SDL_MOUSEWHEEL) {
                if (e.wheel.y > 0) zoom *= 1.05;
                if (e.wheel.y < 0) zoom *= 0.95;
            }
        }

        update_simulation(&sim);
        render_frame(ren, &sim, 900, 700, zoom);

        SDL_Delay(16);
    }

    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
}
