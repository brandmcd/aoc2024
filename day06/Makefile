# Makefile
# Build rules for Advent of Code DayXX

# Compiler
CXX ?= g++

# Compiler flags
CXXFLAGS ?= --std=c++17 -Wall -Werror -pedantic -g -Wno-sign-compare -Wno-comment

# Targets
day06_tests.exe: day06.cpp day06_tests.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

# Default target
.PHONY: all
all: day06_tests.exe
	@echo "Running tests..."
	./day06_tests.exe

# Clean target
.PHONY: clean
clean:
	rm -rvf *.out *.exe *.dSYM *.stackdump
