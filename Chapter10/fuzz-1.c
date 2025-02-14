#include <stdio.h>
#include <string.h>

// Function to parse file content, containing a buffer overflow vulnerability
void parse_file(const char *filename) {
    // Define a fixed-size buffer (64 bytes)
    char buffer[64];
    
    // Open the file
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        printf("Error: Failed to open file %s\n", filename);
        return;
    }

    // Read file content into the buffer, reading 128 bytes, exceeding buffer size
    // This introduces a buffer overflow vulnerability
    fread(buffer, 1, sizeof(buffer), fp);
    
    // Close the file
    fclose(fp);

    // Print buffer content (for debugging purposes only)
    printf("Buffer content: %s\n", buffer);
}

int main(int argc, char *argv[]) {
    // Check command-line arguments
    if (argc != 2) {
        printf("Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    // Call the parsing function
    parse_file(argv[1]);
    return 0;
}