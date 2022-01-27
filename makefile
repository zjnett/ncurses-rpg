CC=gcc
OUT=rpg
SRC=$(wildcard src/*.c)
LDFLAGS=-lcurses -lpanel -lSDL2 -lSDL2_mixer -lm

all: bin ncurses-rpg

ncurses-rpg:
	$(CC) $(SRC) -o bin/$(OUT) $(LDFLAGS)

bin:
	mkdir -p bin

clean:
	rm -r bin
