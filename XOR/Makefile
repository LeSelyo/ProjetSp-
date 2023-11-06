INCL   = $(wildcard *.h)
SRC    = $(wildcard *.c)
OBJ    = $(SRC:.c=.o)
LIBS   = -lm
EXE    = network

CC      = gcc
CFLAGS  = -std=c99 -Wall -O2 -D__NO_INLINE__
LIBPATH = -L.
LDFLAGS = -o $(EXE) $(LIBPATH) $(LIBS)
CFDEBUG = -std=c99c -Wall -g -DDEBUG $(LDFLAGS)
RM      = rm -f

%.o: %.c
	$(CC) -c $(CFLAGS) $*.c

$(EXE): $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS)

$(OBJ): $(INCL)

debug:
	$(CC) $(CFDEBUG) $(SRC)

clean:
	$(RM) $(OBJ) $(EXE) core a.out 

run:
	@./$(EXE) || true