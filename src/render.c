#include "render.h"
#include <math.h>

#define TRAIL_MAX 1000
static struct { double x, y; } trail[TRAIL_MAX];
static int trail_count = 0, trail_next = 0;

void clear_trail() { trail_count = 0; trail_next = 0; }

static void add_trail(double x, double y) {
    trail[trail_next].x = x; trail[trail_next].y = y;
    trail_next = (trail_next + 1) % TRAIL_MAX;
    if (trail_count < TRAIL_MAX) trail_count++;
}

static void draw_bob(SDL_Renderer *r, int cx, int cy, int rad) {
    for (int w = -rad; w <= rad; w++)
        for (int h = -rad; h <= rad; h++)
            if (w*w + h*h <= rad*rad) SDL_RenderDrawPoint(r, cx+w, cy+h);
}

void render_frame(SDL_Renderer *r, Simulation *s, int W, int H, double zoom) {
    // Background
    SDL_SetRenderDrawColor(r, 10, 10, 25, 255);
    SDL_RenderClear(r);

    int ox = W / 2, oy = H / 3;
    double scale = 150 * zoom;
    double x1, y1, x2, y2;

    if (s->mode == 0) {
        x1 = ox + sin(s->single.theta) * s->single.L * scale;
        y1 = oy + cos(s->single.theta) * s->single.L * scale;
        add_trail(x1, y1);
        SDL_SetRenderDrawColor(r, 200, 200, 200, 255);
        SDL_RenderDrawLine(r, ox, oy, (int)x1, (int)y1);
        SDL_SetRenderDrawColor(r, 255, 50, 50, 255);
        draw_bob(r, (int)x1, (int)y1, 15);
    } else {
        x1 = ox + sin(s->dbl.theta1) * s->dbl.L1 * scale;
        y1 = oy + cos(s->dbl.theta1) * s->dbl.L1 * scale;
        x2 = x1 + sin(s->dbl.theta2) * s->dbl.L2 * scale;
        y2 = y1 + cos(s->dbl.theta2) * s->dbl.L2 * scale;
        add_trail(x2, y2);
        SDL_SetRenderDrawColor(r, 180, 180, 180, 255);
        SDL_RenderDrawLine(r, ox, oy, (int)x1, (int)y1);
        SDL_RenderDrawLine(r, (int)x1, (int)y1, (int)x2, (int)y2);
        SDL_SetRenderDrawColor(r, 0, 200, 255, 255);
        draw_bob(r, (int)x1, (int)y1, 10);
        SDL_SetRenderDrawColor(r, 0, 255, 100, 255);
        draw_bob(r, (int)x2, (int)y2, 12);
    }

    // Render Traces (Alpha Blending)
    SDL_SetRenderDrawBlendMode(r, SDL_BLENDMODE_BLEND);
    for (int i = 0; i < trail_count; i++) {
        int idx = (trail_next - i - 1 + TRAIL_MAX) % TRAIL_MAX;
        int alpha = (int)(255 * (1.0 - (double)i / trail_count));
        SDL_SetRenderDrawColor(r, 255, 255, 255, alpha / 2);
        SDL_RenderDrawPoint(r, (int)trail[idx].x, (int)trail[idx].y);
    }
    SDL_RenderPresent(r);
}