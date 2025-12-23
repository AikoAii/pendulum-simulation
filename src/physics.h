#ifndef PHYSICS_H
#define PHYSICS_H

typedef struct {
    double theta, omega, L, m;
} SinglePendulum;

typedef struct {
    double theta1, omega1, theta2, omega2;
    double L1, L2, m1, m2;
} DoublePendulum;

typedef struct {
    union {
        SinglePendulum single;
        DoublePendulum dbl;
    };
    int mode; // 0 = single, 1 = double
    double dt;
    double gravity;
    int paused;
} Simulation;

void init_simulation(Simulation *s, int mode);
void update_simulation(Simulation *s);

#endif