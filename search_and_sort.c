/*
 * Algorithmics and Data Structures - Session 3
 * Searching and Sorting (all in one file)
 *
 * Searching: linear, jump, binary
 * Sorting  : selection, insertion, bubble, merge, quick
 *
 * Compile: gcc search_and_sort.c -o search_and_sort
 */

#include <stdio.h>
#include <stdlib.h>

/* ---------- small helpers ---------- */

void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void print_array(int a[], int n) {
    printf("[");
    for (int i = 0; i < n; i++) {
        printf("%d", a[i]);
        if (i < n - 1) printf(", ");
    }
    printf("]\n");
}

void copy_array(int src[], int dst[], int n) {
    for (int i = 0; i < n; i++) {
        dst[i] = src[i];
    }
}

/* =====================================================
 *                    SEARCHING
 * ===================================================== */

/* Linear search: works on any array. Time O(n), space O(1) */
int linear_search(int a[], int n, int target) {
    for (int i = 0; i < n; i++) {
        if (a[i] == target) return i;
    }
    return -1;
}

/* Jump search: sorted array only. Best jump size = sqrt(n). Time O(sqrt(n)) */
int jump_search(int a[], int n, int target) {
    if (n <= 0) return -1;

    /* find the jump size m (about sqrt(n)) */
    int m = 1;
    while (m * m < n) m++;

    int prev = 0;
    int next = m;

    /* jump block by block while the last element of the block is too small */
    while (a[(next < n ? next : n) - 1] < target) {
        prev = next;
        next = next + m;
        if (prev >= n) return -1;
    }

    /* linear search inside the block */
    int end = (next < n) ? next : n;
    for (int i = prev; i < end; i++) {
        if (a[i] == target) return i;
    }
    return -1;
}

/* Binary search: sorted array only. Time O(log n), space O(1) */
int binary_search(int a[], int n, int target) {
    int low = 0;
    int high = n - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (a[mid] == target) return mid;
        if (a[mid] < target) low = mid + 1;
        else high = mid - 1;
    }
    return -1;
}

/* =====================================================
 *                 SIMPLE SORTING  O(n^2)
 * ===================================================== */

/* Selection sort: find the smallest, put it at the front */
void selection_sort(int a[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min = i;
        for (int j = i + 1; j < n; j++) {
            if (a[j] < a[min]) min = j;
        }
        swap(&a[i], &a[min]);
    }
}

/* Insertion sort: insert each element in the sorted part on its left */
void insertion_sort(int a[], int n) {
    for (int i = 1; i < n; i++) {
        int key = a[i];
        int j = i - 1;
        while (j >= 0 && a[j] > key) {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = key;
    }
}

/* Bubble sort: swap neighbours that are in the wrong order */
void bubble_sort(int a[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int swapped = 0;
        for (int j = 0; j < n - 1 - i; j++) {
            if (a[j] > a[j + 1]) {
                swap(&a[j], &a[j + 1]);
                swapped = 1;
            }
        }
        if (!swapped) break; /* already sorted */
    }
}

/* =====================================================
 *              COMPLEX SORTING  O(n log n)
 * ===================================================== */

/* Merge sort: divide in two halves, sort each, merge them */

/* merge a[left..mid] and a[mid+1..right] (both already sorted) */
void merge(int a[], int tmp[], int left, int mid, int right) {
    int i = left;
    int j = mid + 1;
    int k = left;

    while (i <= mid && j <= right) {
        if (a[i] <= a[j]) tmp[k++] = a[i++];
        else tmp[k++] = a[j++];
    }
    while (i <= mid) tmp[k++] = a[i++];
    while (j <= right) tmp[k++] = a[j++];

    for (k = left; k <= right; k++) {
        a[k] = tmp[k];
    }
}

void merge_sort_rec(int a[], int tmp[], int left, int right) {
    if (left >= right) return;
    int mid = (left + right) / 2;
    merge_sort_rec(a, tmp, left, mid);
    merge_sort_rec(a, tmp, mid + 1, right);
    merge(a, tmp, left, mid, right);
}

void merge_sort(int a[], int n) {
    int *tmp = malloc(n * sizeof(int)); /* extra memory O(n) */
    merge_sort_rec(a, tmp, 0, n - 1);
    free(tmp);
}

/* Quick sort: pivot = last element, smaller on the left, bigger on the right */

int partition(int a[], int low, int high) {
    int pivot = a[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (a[j] <= pivot) {
            i++;
            swap(&a[i], &a[j]);
        }
    }
    swap(&a[i + 1], &a[high]); /* put the pivot at its place */
    return i + 1;
}

void quick_sort(int a[], int low, int high) {
    if (low < high) {
        int p = partition(a, low, high);
        quick_sort(a, low, p - 1);
        quick_sort(a, p + 1, high);
    }
}

/* =====================================================
 *                        MAIN
 * ===================================================== */

int main() {
    /* ----- searching ----- */
    int unsorted[] = {1, -2, 3, 11, 2};
    int sorted[] = {-21, -9, -2, 1, 3, 11, 12, 21, 22};
    int n1 = 5;
    int n2 = 9;

    printf("=== SEARCHING ===\n");
    printf("Linear search of 11 in unsorted array: index %d\n",
           linear_search(unsorted, n1, 11));
    printf("Jump search of 21 in sorted array    : index %d\n",
           jump_search(sorted, n2, 21));
    printf("Binary search of 21 in sorted array  : index %d\n",
           binary_search(sorted, n2, 21));
    printf("Binary search of 100 (not in array)  : index %d\n",
           binary_search(sorted, n2, 100));

    /* ----- sorting ----- */
    int original[] = {8, 3, 1, 7, 0, 10, 2, 5};
    int n = 8;
    int a[8];

    printf("\n=== SORTING ===\n");
    printf("Original      : ");
    print_array(original, n);

    copy_array(original, a, n);
    selection_sort(a, n);
    printf("Selection sort: ");
    print_array(a, n);

    copy_array(original, a, n);
    insertion_sort(a, n);
    printf("Insertion sort: ");
    print_array(a, n);

    copy_array(original, a, n);
    bubble_sort(a, n);
    printf("Bubble sort   : ");
    print_array(a, n);

    copy_array(original, a, n);
    merge_sort(a, n);
    printf("Merge sort    : ");
    print_array(a, n);

    copy_array(original, a, n);
    quick_sort(a, 0, n - 1);
    printf("Quick sort    : ");
    print_array(a, n);

    return 0;
}
