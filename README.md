# epidemic
##Author
Silvia Vicentini
This is a program that simulates the development of an epidemic based on the SIR model. It studies the changing of the variables S I and R through time, it represents a graph of these variables and it studies the epidemic using a cellular automaton.
## Install required packages
This program requires the additional library SFML, you can install it by running the command:
```bash
$ sudo apt install libsfml-dev
```
## Compile and run
To compile the program with CMake run the commands:
```bash
$ cmake -B build -S . -DCMAKE_BUILD_TYPE=Release
$ cmake --build build
```
If you want to develop changes to the program I suggest to compile in Debug mode:
```bash
$ cmake -B build -S . -DCMAKE_BUILD_TYPE=Debug
$ cmake --build build
```
To study the epidemic and the graph displaing the data run the command:
```bash
$ ./build/epidemic_graph
```
To study the epidemic using the cellular automaton run the command:
```bash
$ ./build/cellular_automaton
```
To run the tests execute the commands:
```bash
$ ./build/epidemic.t
$ ./build/graph.t
$ ./build/simulation.t
```
