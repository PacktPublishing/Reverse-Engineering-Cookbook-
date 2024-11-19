#include <stdio.h>
#include <string.h>
#include <windows.h>
#pragma comment(lib, "Advapi32.lib")

#define UNLEN 256

// Function to simulate a long delay by executing a large number of useless loops
void simulate_long_delay_with_loops() {
    volatile unsigned long long i;
    printf("Simulating long delay with a large loop...\n");
    for (i = 0; i < 10000000000ULL; i++) {
        // Empty loop to consume CPU cycles and create delay
        // This could force an emulator to time out or terminate
    }
    printf("Completed the large loop.\n");
}

// Function to check for the presence of a fixed emulator-related username
int check_username() {
    char username[UNLEN + 1] = {0};  // Initialize the buffer with zero
    DWORD username_len = sizeof(username);  // Full size including null terminator

    if (GetUserName(username, &username_len)) {
        printf("Detected username: %s\n", username);
        // Check if the username matches a known emulator-specific name
        if (strcmp(username, "EmulatorUser") == 0 || strcmp(username, "JohnDoe") == 0) {
            printf("Emulator detected based on username.\n");
            return 1;
        }
    } else {
        printf("Failed to retrieve username.\n");
    }

    return 0;
}

int main() {
    if (check_username()) {
        printf("Exiting due to emulator detection.\n");
        return 1;
    }

    simulate_long_delay_with_loops();  // Create a delay using a massive loop
    printf("No emulator detected. Proceeding with normal execution.\n");

    // Proceed with the rest of the application logic
    // ...

    return 0;
}
