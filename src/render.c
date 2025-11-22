#include "render.h"
#include <math.h>
#include <stdio.h>

#define TRAIL_MAX 600

static int trail_count = 0;
static int trail_next = 0;

typedef struct {
    double x, y;
} TrailPoint;

static TrailPoint trail[TRAIL_MAX];

static void add_trail(double x, double y) {
    trail[trail_next].x = x;
    trail[trail_next].y = y;

    trail_next = (trail_next + 1) % TRAIL_MAX;
    if (trail_count < TRAIL_MAX) trail_count++;
}

static void draw_circle(SDL_Renderer *r, int cx, int cy, int radius) {
    for (int w = -radius; w <= radius; w++)
        for (int h = -radius; h <= radius; h++)
            if (w*w + h*h <= radius*radius)
                SDL_RenderDrawPoint(r, cx+w, cy+h);
}

static void draw_text(SDL_Renderer *r, int x, int y, const char *msg) {
    (void)r;
    (void)x;
    (void)y;
    (void)msg;
}


void render_frame(SDL_Renderer *r, Simulation *s, int W, int H, double zoom) {
    SDL_SetRenderDrawColor(r, 15, 15, 20, 255);
    SDL_RenderClear(r);

    int ox = W / 2;
    int oy = H / 4;

    double SCALE = 180 * zoom;

    double x1, y1, x2, y2;

    if (s->mode == 0) {
        x1 = ox + sin(s->single.theta)*s->single.L*SCALE;
        y1 = oy + cos(s->single.theta)*s->single.L*SCALE;
        add_trail(x1, y1);

        SDL_SetRenderDrawColor(r, 240, 240, 240, 255);
        SDL_RenderDrawLine(r, ox, oy, x1, y1);

        SDL_SetRenderDrawColor(r, 200, 120, 255, 255);
        draw_circle(r, x1, y1, 14);
    } else {
        x1 = ox + sin(s->dbl.theta1)*s->dbl.L1*SCALE;
        y1 = oy + cos(s->dbl.theta1)*s->dbl.L1*SCALE;

        x2 = x1 + sin(s->dbl.theta2)*s->dbl.L2*SCALE;
        y2 = y1 + cos(s->dbl.theta2)*s->dbl.L2*SCALE;

        add_trail(x2, y2);

        SDL_SetRenderDrawColor(r, 240, 240, 240, 255);
        SDL_RenderDrawLine(r, ox, oy, x1, y1);
        SDL_RenderDrawLine(r, x1, y1, x2, y2);

        SDL_SetRenderDrawColor(r, 255, 120, 120, 255);
        draw_circle(r, x1, y1, 13);

        SDL_SetRenderDrawColor(r, 120, 200, 255, 255);
        draw_circle(r, x2, y2, 13);
    }

    // Draw trail
    for (int i = 0; i < trail_count; i++) {
        int idx = (trail_next - i - 1 + TRAIL_MAX) % TRAIL_MAX;
        double f = 1.0 - (double)i / trail_count;

        SDL_SetRenderDrawColor(r,
            (int)(80 * f),
            (int)(150 * f),
            (int)(255 * f),
            200);

        SDL_RenderDrawPoint(r, (int)trail[idx].x, (int)trail[idx].y);
    }

    // HUD
    char info[128];
    if (s->mode == 0) {
        snprintf(info, sizeof(info),
                 "MODE: Single | theta=%.2f | omega=%.2f | L=%.2f | zoom=%.2f",
                 s->single.theta, s->single.omega,
                 s->single.L, zoom);
    } else {
        snprintf(info, sizeof(info),
                 "MODE: Double | th1=%.2f th2=%.2f | zoom=%.2f",
                 s->dbl.theta1, s->dbl.theta2, zoom);
    }

    draw_text(r, 10, 10, info);

    SDL_RenderPresent(r);
}
