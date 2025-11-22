#ifndef PHYSICS_H
#define PHYSICS_H

typedef struct {
    double theta;
    double omega;
    double L;
    double m;
} SinglePendulum;

typedef struct {
    double theta1, omega1;
    double theta2, omega2;
    double L1, L2;
    double m1, m2;
} DoublePendulum;

typedef struct {
    SinglePendulum single;
    DoublePendulum dbl;

    int mode; // 0 = single, 1 = double
    double dt;
} Simulation;

void init_single(Simulation *s);
void init_double(Simulation *s);
void update_simulation(Simulation *s);

#endif
