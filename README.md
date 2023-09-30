# ncurses-rpg
An ASCII role-playing game created in ncurses.

## Requirements
* ncurses
* SDL2
* SDL2-mixer

## Usage
Build with `make` executed from the root directory of the project.

The game must be executed from the context of the `bin/` directory due to relative pathnames. Therefore, the game can be built and run as follows:
```
$ make
$ cd bin
$ ./rpg
```

## Issues
* Not tested on Windows platforms.

