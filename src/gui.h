#ifndef GUI_H
#define GUI_H

#include "physics.h"
#include <SDL2/SDL.h>

typedef struct {
    SDL_Window *win;
    SDL_Renderer *ren;
    int running;
} GUI;

int gui_init(GUI *g, const char *title, int w, int h);
void gui_handle_events(GUI *g, Simulation *s);
void gui_destroy(GUI *g);

#endif
