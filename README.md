# Money to Text Conversion Program

"I completed the 03 assignment with functionality to save the cache to a file and reload it, but I wanted to make the files more organized."

This C program converts numeric money values (in cents) to text strings. It also uses memoization to cache results for faster performance.

## Features
- Converts money values like `4734` to `forty.seven dollars and thirty-four cents`.
- Supports memoization for values to improve performance.
- Caches data in a binary file `memo_cache.dat`.
- Handles invalid inputs gracefully.

---

## How to Compile and Run

1. **Compile the Program:**
   ```bash
   make
   ```

2. **Run the Program:**
   ```bash
   ./main
   ```

3. **Clean Build Files:**
   ```bash
   make clean
   ```

---

## Accessing Memoization Cache (`memo_cache.dat`)

### View Cached Data Using `hexdump`:
```bash
hexdump -C memo_cache.dat
```


