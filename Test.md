# Test Cases for Money to Text Conversion

## ✅ Success Test Cases

1. **Input:** `0`
   - **Expected Output:** `zero dollars and zero cents`

2. **Input:** `100`
   - **Expected Output:** `one dollar and zero cents`

3. **Input:** `99`
   - **Expected Output:** `zero dollars and ninety-nine cents`

4. **Input:** `150000`
   - **Expected Output:** `one thousand five hundred dollars and zero cents`

5. **Input:** `500000`
   - **Expected Output:** `five thousand dollars and zero cents`

6. **Input:** `1000000`
   - **Expected Output:** `ten thousand dollars and zero cents`

7. **Input:** `4734`
   - **Expected Output:** `forty.seven dollars and thirty-four cents`

8. **Input:** `1000000000`
   - **Expected Output:** `ten million dollars and zero cents`

---

## ❌ Failure Test Cases


# Negative number:
1. **Input:** `-100`
   - **Expected Output:** `invalid amount`
# More than max limit:
2. **Input:** `1000000001`
   - **Expected Output:** `invalid amount`
# enter a letter:
3. **Input:** `a`
   - **Expected Output:** `Invalid input. Please enter a valid number.`

