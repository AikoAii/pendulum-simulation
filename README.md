# Pendulum Simulation

```txt
simple physics | experiment | C | SDL2 | visualization
```

A simple **pendulum experiment** written in **C** using **SDL2** for visualization.

This project was made to learn:

* basic physics simulation
* numerical integration (RK4)
* low-level graphics rendering with SDL2

Nothing fancy — just experimenting and learning step by step.

---

## How It Works (Simple Explanation)

This simulation does not rely on fake movement or animation tricks.
Everything is calculated using real physics equations.

### 🔹 Single Pendulum

A mass swinging under gravity.
The motion is stable, smooth, and predictable (simple harmonic motion).

### 🔹 Double Pendulum

Two connected pendulums.
This system is **chaotic**, meaning:

* extremely sensitive to initial conditions
* small changes produce very different motion
* beautiful and complex trajectories

### 🔹 RK4 Integrator

Instead of the simple Euler method, this project uses:

```txt
Runge-Kutta 4th Order (RK4)
```

Benefits:

* smoother motion
* better numerical stability
* closer-to-real physics behavior

### 🔹 Motion Trails

The simulation draws the **path** of the pendulum over time,
allowing you to visualize chaos, symmetry, and patterns.

---

## Project Structure

```txt
pendulum-simulation/
├── src/
│   ├── main.c       # Entry point, SDL initialization & input handling
│   ├── physics.c    # RK4 physics logic (single & double pendulum)
│   ├── physics.h    # Data structures & simulation state
│   ├── render.c     # SDL2 drawing logic & motion trails
│   └── render.h     # Rendering headers
├── Makefile         # Build automation (GCC)
└── README.md        # Project documentation
```

---

## Installation

This project requires **SDL2** and **GCC** to be installed on your system.

---

### Linux (Ubuntu / Debian / WSL)

Install dependencies:

```bash
sudo apt update
sudo apt install build-essential libsdl2-dev
```

Build and run:

```bash
make
./pendulum
```

---

### Arch Linux / Manjaro

Install dependencies:

```bash
sudo pacman -S gcc make sdl2
```

Build and run:

```bash
make
./pendulum
```

---

### macOS (Homebrew)

Install Homebrew (if not installed):

```bash
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
```

Install dependencies:

```bash
brew install sdl2
```

Build and run:

```bash
make
./pendulum
```

---

### Windows

Recommended options:

```txt
- MSYS2 (recommended)
- MinGW + SDL2
- WSL (Windows Subsystem for Linux)
```

Using **MSYS2**:

```bash
pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-SDL2 make
```

Then build:

```bash
make
```

---

### Verify Installation

If the program opens a window and shows a swinging pendulum,
your installation is successful.

---

## Controls

```txt
[1]     → Single Pendulum mode
[2]     → Double Pendulum mode (chaotic)
[SPACE] → Pause / Resume simulation
[R]     → Reset simulation
[Scroll]→ Zoom in / Zoom out
[ESC]   → Exit program
```

---

## Screenshots

### Single Pendulum (Press 1)


![Single pendulum](/img/1.png)
Smooth and predictable harmonic motion

### Double Pendulum (Press 2)

![Double pendulum](/img/2.png)
Chaotic, sensitive, and beautiful motion trails

---

## 📐 Pendulum Physics (The Math)

Variables used in the code:

```txt
θ (theta)  : Angle from vertical
ω (omega)  : Angular velocity
L          : Arm length
m          : Mass
g          : Gravity (9.81 m/s²)
dt         : Time step (≈ 0.016 for 60 FPS)
```

### RK4 Formula

```txt
NewState = OldState + (dt / 6) × (k1 + 2k2 + 2k3 + k4)
```

This keeps the simulation stable over long periods of time.

---

## Why I Made This

```txt
- learn numerical physics (RK4)
- practice memory & structure management in C
- experiment with SDL2 rendering
```

---

## Fun Fact

This project was inspired after watching the anime:

```txt
"Chi: On the Movements of the Earth"
(Chikyuu no Undou ni Tsuite)
```

It made me realize how beautiful **motion** can be
when described using mathematics.

---

## 📄 License

MIT License — free to use, modify, remix, and experiment.

```txt
still learning, still experimenting
```
