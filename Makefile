all:
	gcc -Wall -O2 `sdl2-config --cflags` \
	    src/main.c src/physics.c src/render.c \
	    -o pendulum `sdl2-config --libs` -lm
