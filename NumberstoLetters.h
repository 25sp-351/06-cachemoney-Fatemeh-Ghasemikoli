#ifndef NUMBERSTOLETTERS_H
#define NUMBERSTOLETTERS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cache.h"

#define INITIAL_BUFFER_SIZE 64  // Initial buffer size for storing the result
#define MEMOIZE_LIMIT 150000  // Memoization limit for caching
#define MAX_INPUT_LIMIT 1000000000  // Maximum allowed input in cents

// Function Prototypes
const char* convert_money_to_text(int cents); // Convert money to text

void number_to_letter(int num, char *buffer, int is_dollar); // Convert number to letter

#endif // NUMBERSTOLETTERS_H
