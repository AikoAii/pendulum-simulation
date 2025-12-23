CC = gcc
CFLAGS = -Wall -O3 `sdl2-config --cflags`
LIBS = `sdl2-config --libs` -lm
SRC = src/main.c src/physics.c src/render.c
OBJ = pendulum

all:
	$(CC) $(CFLAGS) $(SRC) -o $(OBJ) $(LIBS)

clean:
	rm -f $(OBJ)