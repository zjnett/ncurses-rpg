CC=gcc
OUT=rpg
SRC=$(wildcard src/*.c)
LDFLAGS=-lcurses -lSDL2 -lSDL2_mixer

all: bin ncurses-rpg

ncurses-rpg:
	$(CC) $(SRC) -o bin/$(OUT) $(LDFLAGS)

bin:
	mkdir -p bin

clean:
	rm -r bin