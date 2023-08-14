#include <stdio.h>
#include <stdbool.h>

#define MAX_FRAMES 100

int main() {
    int numFrames, numPages;
    printf("Enter the number of frames: ");
    scanf("%d", &numFrames);
    printf("Enter the number of pages: ");
    scanf("%d", &numPages);

    int frames[MAX_FRAMES]; // Array to hold the frame contents
    int pageQueue[MAX_FRAMES]; // Queue to keep track of page order
    int front = 0, rear = 0; // Pointers for queue

    for (int i = 0; i < numFrames; i++) {
        frames[i] = -1; // Initialize frames with an invalid page number
    }

    printf("Enter the page references: ");
    for (int i = 0; i < numPages; i++) {
        int page;
        scanf("%d", &page);

        // Check if the page is already in a frame
        bool pageFound = false;
        for (int j = 0; j < numFrames; j++) {
            if (frames[j] == page) {
                pageFound = true;
                break;
            }
        }

        if (!pageFound) {
            if (rear < numFrames) {
                frames[rear] = page; // Add the page to an empty frame
                rear++;
            } else {
                // Replace the oldest page using FIFO
                frames[front] = page;
                front = (front + 1) % numFrames;
            }

            // Update the page queue for visualization purposes
            pageQueue[rear - 1] = page;
        }

        // Print the current state of frames and page queue
        printf("Frames: ");
        for (int j = 0; j < numFrames; j++) {
            printf("%d ", frames[j]);
        }
        printf("\nPage Queue: ");
        for (int j = 0; j < rear; j++) {
            printf("%d ", pageQueue[j]);
        }
        printf("\n");
    }

    return 0;
}

