#include "NumberstoLetters.h"
#include "cache.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_BUFFER_SIZE 64 // Initial buffer size for storing the result

const char *units[] = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"};  
const char *tens[] = {"", "", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"};

char *memo[MEMOIZE_LIMIT]; // Memoization cache

// Function to convert a number to its equivalent letter representation
void number_to_letter(int num, char *buffer, int is_dollar) {
    if (num < 20) {
        strncat(buffer, units[num], 256 - strlen(buffer) - 1);
    } else if (num < 100) {
        strncat(buffer, tens[num / 10], 256 - strlen(buffer) - 1);
        if (num % 10) {
            strncat(buffer, is_dollar ? "." : "-", 256 - strlen(buffer) - 1);
            strncat(buffer, units[num % 10], 256 - strlen(buffer) - 1);
        }
    } else {
        int divisor;
        const char *suffix;

        if (num >= 1000000000) {
            divisor = 1000000000;
            suffix = " billion";
        } else if (num >= 1000000) {
            divisor = 1000000;
            suffix = " million";
        } else if (num >= 1000) {
            divisor = 1000;
            suffix = " thousand";
        } else {
            divisor = 100;
            suffix = " hundred";
        }

        number_to_letter(num / divisor, buffer, is_dollar);
        strncat(buffer, suffix, 256 - strlen(buffer) - 1);

        int remainder = num % divisor;
        if (remainder > 0) {
            strncat(buffer, " ", 256 - strlen(buffer) - 1);
            number_to_letter(remainder, buffer, is_dollar);
        }
    }
}


// Function to convert money to text
const char* convert_money_to_text(int cents) {  
    if (cents < 0 || cents > MAX_INPUT_LIMIT) return "invalid amount";
    if (cents < MEMOIZE_LIMIT && memo[cents]) return memo[cents];

    size_t buffer_size = INITIAL_BUFFER_SIZE; // Initial buffer size
    char *result = malloc(buffer_size);
    if (!result) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    result[0] = '\0';

    int dollars = cents / 100;
    int rem_cents = cents % 100;

    // Ensure enough space for dollar conversion
    size_t needed = buffer_size + 20;
    result = realloc(result, needed);
    if (!result) {
        perror("Memory reallocation failed");
        exit(EXIT_FAILURE);
    }

    if (dollars) {
        number_to_letter(dollars, result, 1);
        snprintf(result + strlen(result), needed - strlen(result), " dollar%s", (dollars > 1) ? "s" : "");
    } else {
        strncat(result, "zero dollars", needed - strlen(result) - 1);
    }

    strncat(result, " and ", needed - strlen(result) - 1);

    // Ensure enough space for cents conversion
    needed = strlen(result) + 20;
    result = realloc(result, needed);
    if (!result) {
        perror("Memory reallocation failed");
        exit(EXIT_FAILURE);
    }

    if (rem_cents) {
        number_to_letter(rem_cents, result, 0);
        snprintf(result + strlen(result), needed - strlen(result), " cent%s", (rem_cents > 1) ? "s" : "");
    } else {
        strncat(result, "zero cents", needed - strlen(result) - 1);
    }

    // Memoization storage (ensure index validity)
    if (cents < MEMOIZE_LIMIT) {
        if (memo[cents]) free(memo[cents]);  // Free old memory if needed
        memo[cents] = strdup(result); // Store result
    }

    return result; 
}
