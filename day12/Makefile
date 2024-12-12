# Makefile
# Build rules for Advent of Code DayXX

# Compiler
CXX ?= g++

# Compiler flags
CXXFLAGS ?= --std=c++17 -Wall -Werror -pedantic -g -Wno-sign-compare -Wno-comment

# Targets
day12_tests.exe: day12.cpp day12_tests.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

# Default target
.PHONY: all
all: day12_tests.exe
	@echo "Running tests..."
	./day12_tests.exe

# Clean target
.PHONY: clean
clean:
	rm -rvf *.out *.exe *.dSYM *.stackdump
