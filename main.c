#include "NumberstoLetters.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

// Function to handle SIGINT signal
void handle_sigint() {  
    printf("\nCaught SIGINT (Ctrl+C), saving cache...\n");
    save_cache();
    exit(0);
}

int main() {
    load_cache();  // Load the cache from file
    signal(SIGINT, handle_sigint); // Register the signal handler for SIGINT

    int cents;
    printf("Enter money values in cents 'Ctrl+C to end':\n");

    // Loop to read input from the user
    while (1) { 
        if (scanf("%d", &cents) == 1) {
            if (cents < 0 || cents > MAX_INPUT_LIMIT) {
                printf("%d = invalid amount\n", cents);
                continue;
            }

            const char *result = convert_money_to_text(cents);
            printf("%d = %s\n", cents, result);

        } else if (feof(stdin)) {
            break;
        } else {
            printf("INVALID = Invalid input. Please enter a valid number.\n");
            while (getchar() != '\n');
        }
    }

    save_cache();

    return 0;
}
