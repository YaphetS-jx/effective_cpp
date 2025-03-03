#!/bin/bash

# Check if at least one argument (the file names) is provided.
if [ "$#" -lt 1 ]; then
    echo "Usage: $0 <filename1.cpp> <filename2.cpp> ..."
    exit 1
fi

# Define the source files path.
SOURCE_FILES=""
for FILE in "$@"; do
    SOURCE_FILE="src/$FILE"
    # Verify that the source file exists.
    if [ ! -f "$SOURCE_FILE" ]; then
        echo "Error: File '$SOURCE_FILE' not found!"
        exit 1
    fi
    SOURCE_FILES="$SOURCE_FILES $SOURCE_FILE"
done

# Compile the source files using g++ and output the executable named 'test'.
g++ -o test $SOURCE_FILES

# Check if the compilation was successful.
if [ "$?" -eq 0 ]; then
    echo "Compilation successful. Executable 'test' created."
else
    echo "Compilation failed."
    exit 1
fi

# Run the executable
./test