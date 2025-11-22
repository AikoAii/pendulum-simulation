#ifndef RENDER_H
#define RENDER_H

#include <SDL2/SDL.h>
#include "physics.h"

void render_frame(SDL_Renderer *r, Simulation *s, int w, int h,
                  double zoom);

#endif
