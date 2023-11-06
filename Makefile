# Makefile

CC=gcc -I./image_processing -I./grid_processing -I./utils -I./grid_splitting -I./sudoku_solver

CPPFLAGS= `pkg-config --cflags gtk+-3.0` `pkg-config --cflags sdl2` -D__NO_INLINE__
CFLAGS=  -g -fsanitize=address -Wall -Wextra  -std=c99 -O0
LDFLAGS= -fsanitize=address 
LDLIBS= -lasan `pkg-config --libs gtk+-3.0` `pkg-config --libs sdl2` -lSDL2_image -lm -lpthread

SRC=$(wildcard image_processing/*.c) $(wildcard grid_splitting/*.c) $(wildcard utils/*.c) $(wildcard grid_processing/*.c)  sudoku_solver/solver.c
OBJ=$(SRC:.c=.o)
DEP=$(SRC:.c=.d)

all: solver sudoku-ocr  


solver:
	make -C ./sudoku_solver

sudoku-ocr: sudoku-ocr.o $(OBJ)


clean-output:
	${RM} *.bmp
	${RM} *.csv
	${RM} ./**/*.bmp
	${RM} ./**/*.csv
	${RM} -r ./assets/output/*

clean: clean-output
	${RM} $(OBJ) $(DEP) main
	make clean -C ./sudoku_solver
	make clean -C ./XOR

# END
