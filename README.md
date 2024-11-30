# Advent of Code 2024 Solutions

This repository contains my solutions for this year's Advent of Code, made in C++. 
The Makefiles and unit test framework are adapted from EECS 280.

Each solution is contained in a folder named `dayXX`, which includes the Makefile. Running `make all` in the `dayXX` directory will compile the solution and the tests. Executing `dayXX_tests.exe` will run both parts of the solution, with all parsing and calculating code located in `dayXX.cpp`.

To create a new day, run these commands (replace `00` with the day number):

```bash
cd ~/AOC/aoc2024
./create_day.sh 00
```

if you get error `./create_day.sh: Permission denied`
`chmod +x create_day.sh`