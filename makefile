CC=gcc
OUT=rpg
SRC=$(wildcard src/*.c)
CFLAGS=
LDFLAGS=-lcurses -lpanel -lSDL2 -lSDL2_mixer -lm

# Detect OS
ifeq ($(OS), Windows_NT)
	detected_OS := Windows
else
	detected_OS := $(shell uname)
endif

ifeq ($(detected_OS), Linux)
	CFLAGS += -fcommon
endif

all: bin ncurses-rpg

ncurses-rpg:
	$(CC) $(CFLAGS) $(SRC) -o bin/$(OUT) $(LDFLAGS)

bin:
	mkdir -p bin

clean:
	rm -r bin
