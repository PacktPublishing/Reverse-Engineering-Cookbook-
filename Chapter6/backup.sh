#!/bin/bash

# Define variables
name=John
file=/tmp/myfile.txt

# Print welcome message
echo Welcome $name

# Create a file and write some content to it
echo "This is a test" > $file

# Prompt the user for a directory and delete all files in it
read -p "Enter directory to clean: " dir
rm -rf $dir/*

# Append the file's content to another file
cat $file >> /tmp/anotherfile.txt

