#include <stdio.h>
#include <stdlib.h>

#define MAX 1000 // Maximum number of disk requests
#define HEAD_POS 53 // Initial position of disk head

// Function to sort disk requests in ascending order
void sortRequests(int requests[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (requests[j] > requests[j + 1]) {
                int temp = requests[j];
                requests[j] = requests[j + 1];
                requests[j + 1] = temp;
            }
        }
    }
}

// Function to implement SCAN scheduling algorithm
void SCAN(int requests[], int n, int headPos) {
    sortRequests(requests, n);

    int totalSeek = 0;
    int direction = 1; // 1 for moving towards higher cylinders, -1 for lower cylinders

    printf("Seek Sequence: %d ", headPos);

    int currentPos = headPos;
    int index;

    // Find the index where headPos is located in the sorted requests
    for (index = 0; index < n; index++) {
        if (requests[index] >= headPos) {
            break;
        }
    }

    // Handle requests in the current direction
    for (int i = index; i < n && i >= 0; i += direction) {
        totalSeek += abs(requests[i] - currentPos);
        currentPos = requests[i];
        printf("%d ", requests[i]);
    }

    // Change direction and handle remaining requests
    direction *= -1;
    for (int i = index - direction; i >= 0 && i < n; i += direction) {
        totalSeek += abs(requests[i] - currentPos);
        currentPos = requests[i];
        printf("%d ", requests[i]);
    }

    printf("\nTotal Seek Distance: %d\n", totalSeek);
}

int main() {
    int requests[MAX];
    int n;

    printf("Enter the number of disk requests: ");
    scanf("%d", &n);

    printf("Enter the disk requests: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &requests[i]);
    }

    SCAN(requests, n, HEAD_POS);

    return 0;
}

