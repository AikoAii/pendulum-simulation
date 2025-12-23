#include <SDL2/SDL.h>
#include "physics.h"
#include "render.h"

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) return 1;

    SDL_Window *win = SDL_CreateWindow("Super Pendulum Lab", 
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 700, SDL_WINDOW_SHOWN);
    SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

    Simulation sim;
    init_simulation(&sim, 1); // Mulai dengan Double Pendulum

    double zoom = 1.0;
    int running = 1;

    while (running) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) running = 0;
            if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    case SDLK_1: init_simulation(&sim, 0); clear_trail(); break;
                    case SDLK_2: init_simulation(&sim, 1); clear_trail(); break;
                    case SDLK_SPACE: sim.paused = !sim.paused; break;
                    case SDLK_r: init_simulation(&sim, sim.mode); clear_trail(); break;
                    case SDLK_ESCAPE: running = 0; break;
                }
            }
            if (e.type == SDL_MOUSEWHEEL) {
                if (e.wheel.y > 0) zoom *= 1.1;
                else zoom *= 0.9;
            }
        }

        update_simulation(&sim);
        render_frame(ren, &sim, 1000, 700, zoom);
        SDL_Delay(16); // Stabilkan di ~60 FPS
    }

    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}