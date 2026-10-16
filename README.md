# Searching and Sorting in C

Algorithmics and Data Structures, Session 3 (ENSISA, Université Haute-Alsace).

Files:

- `search_and_sort.c`: searching and sorting algorithms (Session 3)
- `fibonacci.c`: Fibonacci, iterative (dynamic) vs naive recursive
- `premiers.c`: count the prime numbers up to n, naive vs sieve (needs `-lm` to compile)

## What is inside

| Searching | Sorting (simple) | Sorting (complex) |
|-----------|------------------|-------------------|
| Linear search | Selection sort | Merge sort |
| Jump search | Insertion sort | Quick sort |
| Binary search | Bubble sort | |

## Compile and run

```
gcc search_and_sort.c -o search_and_sort
./search_and_sort
```

## Complexity (average)

| Algorithm | Time | Space |
|-----------|------|-------|
| Linear search | O(n) | O(1) |
| Jump search | O(sqrt(n)) | O(1) |
| Binary search | O(log n) | O(1) |
| Selection / Insertion / Bubble | O(n^2) | O(1) |
| Merge sort | O(n log n) | O(n) |
| Quick sort | O(n log n) | O(log n) |
