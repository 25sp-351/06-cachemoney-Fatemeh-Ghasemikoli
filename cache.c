#include "cache.h"

#define CACHE_FILE "memo_cache.dat"

char *memo[MEMOIZE_LIMIT]; // Memoization cache

void save_cache() { 
    FILE *file = fopen(CACHE_FILE, "wb"); // Open the cache file for writing in binary mode
    if (!file) {
        perror("Error opening file for writing"); // Print error if file cannot be opened
        return;
    }

    for (int i = 0; i < MEMOIZE_LIMIT; i++) {
        if (memo[i] != NULL) { // Check if there is a memoized value at this index
            size_t len = strlen(memo[i]) + 1;
            if (len > 256) continue; // Skip if the length exceeds the buffer size
            fwrite(&i, sizeof(int), 1, file); // Write the index to the file
            fwrite(&len, sizeof(size_t), 1, file); // Write the length of the string to the file
            fwrite(memo[i], sizeof(char), len, file); // Write the string to the file
        }
    }
    fclose(file); // Close the file
}
  
void load_cache() {  // Load cache from file
    FILE *file = fopen(CACHE_FILE, "rb");    
    if (file) {
        int key;
        size_t len;
        char buffer[256];
        while (fread(&key, sizeof(int), 1, file) == 1 && // Read the index
               fread(&len, sizeof(size_t), 1, file) == 1 &&
               fread(buffer, sizeof(char), len, file) == len) {
            if (key < MEMOIZE_LIMIT) {  
                memo[key] = strdup(buffer);
            }
        }
        fclose(file); // Close the file
    }
}
