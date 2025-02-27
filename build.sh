#!/bin/bash

# Check if exactly one argument (the file name) is provided.
if [ "$#" -ne 1 ]; then
    echo "Usage: $0 <filename.cpp>"
    exit 1
fi

# Define the source file path.
SOURCE_FILE="src/$1"

# Verify that the source file exists.
if [ ! -f "$SOURCE_FILE" ]; then
    echo "Error: File '$SOURCE_FILE' not found!"
    exit 1
fi

# Compile the source file using g++ and output the executable named 'test'.
g++ -o test "$SOURCE_FILE"

# Check if the compilation was successful.
if [ "$?" -eq 0 ]; then
    echo "Compilation successful. Executable 'test' created."
else
    echo "Compilation failed."
    exit 1
fi
