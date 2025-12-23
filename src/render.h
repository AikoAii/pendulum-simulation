#ifndef RENDER_H
#define RENDER_H

#include <SDL2/SDL.h>
#include "physics.h"

void render_frame(SDL_Renderer *r, Simulation *s, int W, int H, double zoom);
void clear_trail();

#endif