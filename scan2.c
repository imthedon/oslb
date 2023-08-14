#include <stdio.h>
#include <stdlib.h>

#define MAX_REQUESTS 1000

// Comparator function used for sorting requests
int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

// Function to perform SCAN disk scheduling
void scan(int requests[], int n, int headPos) {
    int totalSeek = 0;
    int direction = 1;  // 1 for moving towards higher cylinders, -1 for lower cylinders

    qsort(requests, n, sizeof(int), compare);

    // Find the index where headPos is located or should be inserted
    int index = 0;
    while (index < n && requests[index] < headPos) {
        index++;
    }

    // Handle requests in the current direction
    for (int i = index; i < n && i >= 0; i += direction) {
        totalSeek += abs(requests[i] - headPos);
        headPos = requests[i];
        printf("%d ", headPos);
    }

    // Change direction and handle remaining requests
    direction *= -1;
    for (int i = index - direction; i >= 0 && i < n; i += direction) {
        totalSeek += abs(requests[i] - headPos);
        headPos = requests[i];
        printf("%d ", headPos);
    }

    printf("\nTotal Seek Distance: %d\n", totalSeek);
}

int main() {
    int requests[MAX_REQUESTS];
    int n, headPos;

    printf("Enter the number of disk requests: ");
    scanf("%d", &n);

    printf("Enter the disk requests: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &requests[i]);
    }

    printf("Enter the initial head position: ");
    scanf("%d", &headPos);

    scan(requests, n, headPos);

    return 0;
}

