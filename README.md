# epidemic
This is a program that simulates the development of an epidemic based on the SIR model. It studies the changing of the variables S I and R through time, it represents a graph of these variables and it studies the epidemic using a cellular automaton.
## Install required packages
This program requires the additional library SFML, you can install it by running the command:
```bash
$ sudo apt install libsfml-dev
```
## Compile and run
To compile the program run the commands:
```bash
$ cmake -B build -S . -DCMAKE_BUILD_TYPE=Release
$ cmake --build build
```
If you want to develop changes to the program I suggest to compile in Debug mode:
```bash
$ cmake -B build -S . -DCMAKE_BUILD_TYPE=Debug
$ cmake --build build
```
