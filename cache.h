#ifndef CACHE_H
#define CACHE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MEMOIZE_LIMIT 150000  // Memoization limit for caching
#define CACHE_FILE "memo_cache.dat"

extern char *memo[MEMOIZE_LIMIT];

void save_cache(); // Save cache to file
void load_cache(); // Load cache from file

#endif // CACHE_H