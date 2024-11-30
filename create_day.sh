#!/bin/bash

# Check if a new day number is provided
if [ -z "$1" ]; then
    echo "Usage: $0 <new_day_number>"
    exit 1
fi

# Set the variables
NEW_DAY=$1
SRC_DIR="dayXX"
DEST_DIR="day${NEW_DAY}"

# Change to the AOC directory
cd ~/AOC/aoc2024 || { echo "Failed to change directory to ~/AOC/aoc2024"; exit 1; }

# Copy the source directory to the new directory
cp -r "$SRC_DIR" "$DEST_DIR"

# Replace all instances of 'dayXX' with the new day in files
find "$DEST_DIR" -type f -exec sed -i "s/$SRC_DIR/$DEST_DIR/g" {} +

# Rename files and directories containing 'dayXX'
find "$DEST_DIR" -depth -name "*$SRC_DIR*" -exec bash -c 'mv "$0" "${0//dayXX/day'"$NEW_DAY"'}"' {} \;

# Change to the new day directory
cd "$DEST_DIR" || { echo "Failed to change directory to $DEST_DIR"; exit 1; }

echo "Setup for day${NEW_DAY} completed successfully!"
