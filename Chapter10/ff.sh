#!/bin/bash

# Check if the user provided an argument, otherwise default to 10
iterations=${1:-10}

for ((i=1; i<=iterations; i++)); do
    echo "Iteration $i/$iterations"

    # Generate malformed PNG files
    ./png-fuzzer fuzz test.png
    
    # Start the display process to view the PNG
    display test.png &

    # Wait for 1 second to allow display to load the PNG
    sleep 1s
    
    pkill -9 display
done

echo "Fuzzing completed!"
exit 0
