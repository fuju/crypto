#!/bin/bash

# Check if the file argument is provided
if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>"
    exit 1
fi

# Check if the file exists
if [ ! -f "$1" ]; then
    echo "File $1 not found"
    exit 1
fi

# Loop through each line in the file
counter=1
while IFS= read -r line; do
    # Execute your command with the line as an argument
    echo "Executing command with argument: $line $counter"
    # Replace "your_command" with the command you want to execute
    ./encgpt.exe "$line"
    ((counter++))
done < "$1"
