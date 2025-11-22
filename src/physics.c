#include "physics.h"
#include <math.h>

#define G 9.81

void init_single(Simulation *s) {
    s->single.theta = 1.2;
    s->single.omega = 0.0;
    s->single.L = 1.0;
    s->single.m = 1.0;
}

void init_double(Simulation *s) {
    s->dbl.theta1 = 1.2;
    s->dbl.theta2 = -0.5;
    s->dbl.omega1 = 0;
    s->dbl.omega2 = 0;
    s->dbl.L1 = 1.0;
    s->dbl.L2 = 1.0;
    s->dbl.m1 = 1.0;
    s->dbl.m2 = 1.0;
}

// Euler method for single
static void step_single(Simulation *s) {
    double th = s->single.theta;
    double om = s->single.omega;

    double alpha = -(G / s->single.L) * sin(th);

    om += alpha * s->dt;
    th += om * s->dt;

    s->single.theta = th;
    s->single.omega = om;
}

// RK4 for double pendulum 
static void step_double(Simulation *s) {
    double t1 = s->dbl.theta1;
    double t2 = s->dbl.theta2;
    double w1 = s->dbl.omega1;
    double w2 = s->dbl.omega2;

    double L1 = s->dbl.L1, L2 = s->dbl.L2;
    double m1 = s->dbl.m1, m2 = s->dbl.m2;

    double dt = s->dt;

    for (int i = 0; i < 2; i++) {
        double num1 = -G*(2*m1+m2)*sin(t1)
                      - m2*G*sin(t1-2*t2)
                      - 2*sin(t1-t2)*m2*(w2*w2*L2 + w1*w1*L1*cos(t1-t2));
        double den1 = L1*(2*m1+m2 - m2*cos(2*t1-2*t2));
        double a1 = num1/den1;

        double num2 = 2*sin(t1-t2)*
                      (w1*w1*L1*(m1+m2)
                       + G*(m1+m2)*cos(t1)
                       + w2*w2*L2*m2*cos(t1-t2));
        double den2 = L2*(2*m1+m2 - m2*cos(2*t1-2*t2));
        double a2 = num2/den2;

        w1 += a1 * dt;
        w2 += a2 * dt;
        t1 += w1 * dt;
        t2 += w2 * dt;
    }

    s->dbl.theta1 = t1;
    s->dbl.theta2 = t2;
    s->dbl.omega1 = w1;
    s->dbl.omega2 = w2;
}

void update_simulation(Simulation *s) {
    if (s->mode == 0) step_single(s);
    else step_double(s);
}
