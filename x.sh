#!/bin/bash

# Define the directory where .c files are located
directory="./"

# Go to the directory
cd "$directory" || exit

# Loop through each .c file
for file in *.c; do
    # Create a temporary file
    tmp_file=$(mktemp)

    # Remove // comments from the file and save the result to the temporary file
    sed 's|//.*$||' "$file" > "$tmp_file"

    # Replace the original file with the temporary file
    mv "$tmp_file" "$file"
done

