# Makefile
# Build rules for Advent of Code DayXX

# Compiler
CXX ?= g++

# Compiler flags
CXXFLAGS ?= --std=c++17 -Wall -Werror -pedantic -g -Wno-sign-compare -Wno-comment

# Targets
day10_tests.exe: day10.cpp day10_tests.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

# Default target
.PHONY: all
all: day10_tests.exe
	@echo "Running tests..."
	./day10_tests.exe

# Clean target
.PHONY: clean
clean:
	rm -rvf *.out *.exe *.dSYM *.stackdump
