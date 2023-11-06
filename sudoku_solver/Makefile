# Makefile

CC=gcc -I../image_processing -I../grid_transform -I../utils -I../grid_splitting -I../sudoku_solver
CPPFLAGS= `pkg-config --cflags gtk+-3.0` `pkg-config --cflags sdl2` -D__NO_INLINE__
CFLAGS= -Wall -Wextra  -std=c99 -O3 -g -fsanitize=address
LDFLAGS= -fsanitize=address 
LDLIBS= `pkg-config --libs gtk+-3.0` `pkg-config --libs sdl2` -lSDL2_image -lm -lpthread

SRC=solver.c $(wildcard ../image_processing/*.c) $(wildcard ../grid_splitting/*.c) $(wildcard ../utils/*.c) $(wildcard ../grid_transform/*.c)
OBJ=$(SRC:.c=.o)
DEP=$(SRC:.c=.d)

all: solver

solver: $(OBJ) main.o 

clean:
	${RM} $(OBJ) $(DEP) main

# END