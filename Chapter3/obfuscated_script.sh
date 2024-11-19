#!/bin/bash

# Generate variables v1 and v2 using base64 encoding and decoding
v1=$(echo -n "J" | base64)  # "J" encoded as base64
v2=$(echo -n "im" | base64) # "im" encoded as base64

# Obfuscate the base64 results and decode them
v1=$(echo "$v1" | base64 -d)  # Decoded as "J"
v2=$(echo "$v2" | base64 -d)  # Decoded as "im"

# Concatenate and convert to hexadecimal format, then convert back to a string
v4=$(echo -n "${v1}${v2}" | hexdump -v -e '/1 "%02x"')  # Convert to hexadecimal
v4=$(echo "$v4" | sed 's/6a69/4a69/')  # Use sed to replace specific values

# Convert the hexadecimal back to the text "Jim"
v4=$(echo "$v4" | xxd -r -p)

# Generate and decode "Welcome"
o=$(echo -n "Welcome" | base64)  # Encode as base64
o=$(echo "$o" | base64 -d)       # Decode to "Welcome"

# Output the final welcome message
echo "$o, $v4!"

