#include "gui.h"
#include <SDL2/SDL.h>

int gui_init(GUI *g, const char *title, int w, int h) {
    SDL_Init(SDL_INIT_VIDEO);

    g->win = SDL_CreateWindow(title,
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              w, h, SDL_WINDOW_SHOWN);

    g->ren = SDL_CreateRenderer(g->win, -1, SDL_RENDERER_ACCELERATED);
    g->running = 1;

    return 1;
}

void gui_handle_events(GUI *g, Simulation *s) {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT)
            g->running = 0;
        if (e.type == SDL_KEYDOWN) {
            if (e.key.keysym.sym == SDLK_1) s->mode = 0;
            if (e.key.keysym.sym == SDLK_2) s->mode = 1;
        }
    }
}

void gui_destroy(GUI *g) {
    SDL_DestroyRenderer(g->ren);
    SDL_DestroyWindow(g->win);
    SDL_Quit();
}
