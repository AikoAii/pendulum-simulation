#include "physics.h"
#include <math.h>

#define G 9.81

void init_simulation(Simulation *s, int mode) {
    s->mode = mode;
    s->gravity = G;
    s->dt = 0.016; // 60 FPS
    s->paused = 0;

    if (mode == 0) {
        s->single.theta = 1.5; // Starting angle
        s->single.omega = 0.0;
        s->single.L = 1.2;     // Sleeve length
        s->single.m = 1.0;
    } else {
        s->dbl.theta1 = 1.5; s->dbl.theta2 = 1.5;
        s->dbl.omega1 = 0.0; s->dbl.omega2 = 0.0;
        s->dbl.L1 = 1.0;     s->dbl.L2 = 1.0;
        s->dbl.m1 = 1.0;     s->dbl.m2 = 1.0;
    }
}

// Calculate angular acceleration for a double pendulum (Lagrange's Equation)
static void double_accel(Simulation *s, double t1, double w1, double t2, double w2, double *a1, double *a2) {
    double m1 = s->dbl.m1, m2 = s->dbl.m2, L1 = s->dbl.L1, L2 = s->dbl.L2, g = s->gravity;
    
    double num1 = -g*(2*m1+m2)*sin(t1) - m2*g*sin(t1-2*t2) - 2*sin(t1-t2)*m2*(w2*w2*L2 + w1*w1*L1*cos(t1-t2));
    double den1 = L1*(2*m1+m2 - m2*cos(2*t1-2*t2));
    *a1 = num1 / den1;

    double num2 = 2*sin(t1-t2)*(w1*w1*L1*(m1+m2) + g*(m1+m2)*cos(t1) + w2*w2*L2*m2*cos(t1-t2));
    double den2 = L2*(2*m1+m2 - m2*cos(2*t1-2*t2));
    *a2 = num2 / den2;
}

void update_simulation(Simulation *s) {
    if (s->paused) return;
    double dt = s->dt;

    if (s->mode == 0) {
        // RK4 Single Pendulum
        double th = s->single.theta, om = s->single.omega;
        double gL = - (s->gravity / s->single.L);

        double kv1 = gL * sin(th);
        double kp1 = om;
        double kv2 = gL * sin(th + 0.5 * dt * kp1);
        double kp2 = om + 0.5 * dt * kv1;
        double kv3 = gL * sin(th + 0.5 * dt * kp2);
        double kp3 = om + 0.5 * dt * kv2;
        double kv4 = gL * sin(th + dt * kp3);
        double kp4 = om + dt * kv3;

        s->single.omega += (dt / 6.0) * (kv1 + 2*kv2 + 2*kv3 + kv4);
        s->single.theta += (dt / 6.0) * (kp1 + 2*kp2 + 2*kp3 + kp4);
    } else {
        // RK4 Double Pendulum
        double t1 = s->dbl.theta1, w1 = s->dbl.omega1;
        double t2 = s->dbl.theta2, w2 = s->dbl.omega2;
        double ka1, ka2, kb1, kb2, kc1, kc2, kd1, kd2;

        double_accel(s, t1, w1, t2, w2, &ka1, &ka2);
        double_accel(s, t1 + 0.5*dt*w1, w1 + 0.5*dt*ka1, t2 + 0.5*dt*w2, w2 + 0.5*dt*ka2, &kb1, &kb2);
        double_accel(s, t1 + 0.5*dt*(w1 + 0.5*dt*kb1), w1 + 0.5*dt*kb1, t2 + 0.5*dt*(w2 + 0.5*dt*kb2), w2 + 0.5*dt*kb2, &kc1, &kc2);
        double_accel(s, t1 + dt*(w1 + dt*kc1), w1 + dt*kc1, t2 + dt*(w2 + dt*kc2), w2 + dt*kc2, &kd1, &kd2);

        s->dbl.omega1 += (dt/6.0)*(ka1 + 2*kb1 + 2*kc1 + kd1);
        s->dbl.theta1 += dt*w1; 
        s->dbl.omega2 += (dt/6.0)*(ka2 + 2*kb2 + 2*kc2 + kd2);
        s->dbl.theta2 += dt*w2;
    }
}