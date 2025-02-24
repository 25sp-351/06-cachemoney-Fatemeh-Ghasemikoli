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
        snprintf(buffer + strlen(buffer), 256 - strlen(buffer), "%s", units[num]);
    } else if (num < 100) {
        snprintf(buffer + strlen(buffer), 256 - strlen(buffer), "%s", tens[num / 10]);
        if (num % 10) {
            snprintf(buffer + strlen(buffer), 256 - strlen(buffer), "%s%s", is_dollar ? "." : "-", units[num % 10]);
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
        snprintf(buffer + strlen(buffer), 256 - strlen(buffer), "%s", suffix);

        int remainder = num % divisor;
        if (remainder > 0) {
            snprintf(buffer + strlen(buffer), 256 - strlen(buffer), " ");
            number_to_letter(remainder, buffer, is_dollar);
        }
    }
}

// Function to convert money to text
const char* convert_money_to_text(int cents) {  
    if (cents < 0 || cents > MAX_INPUT_LIMIT) return "invalid amount";
    
    // Check if result is in memoization cache
    if (cents < MEMOIZE_LIMIT && memo[cents]) {
        printf("Retrieving from memo: ");
        return memo[cents];
    }

    size_t buffer_size = INITIAL_BUFFER_SIZE;
    char *result = malloc(buffer_size);
    if (!result) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    result[0] = '\0';

    int dollars = cents / 100;
    int rem_cents = cents % 100;

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
        snprintf(result + strlen(result), needed - strlen(result), "zero dollars");
    }

    snprintf(result + strlen(result), needed - strlen(result), " and ");

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
        snprintf(result + strlen(result), needed - strlen(result), "zero cents");
    }

    // Memoization storage
    if (cents < MEMOIZE_LIMIT) {
        if (memo[cents]) free(memo[cents]);
        memo[cents] = strdup(result);
        printf("Memoizing:  ");  // Print memoization message
    }

    return result;
}
