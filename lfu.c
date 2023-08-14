#include <stdio.h>
#include <stdbool.h>

#define MAX_FRAMES 100
#define MAX_PAGES 100

struct Page {
    int pageId;
    int frequency;
};

int findLFUPage(struct Page pages[], int numPages) {
    int minFrequency = pages[0].frequency;
    int lfuPageIndex = 0;

    for (int i = 1; i < numPages; i++) {
        if (pages[i].frequency < minFrequency) {
            minFrequency = pages[i].frequency;
            lfuPageIndex = i;
        }
    }

    return lfuPageIndex;
}

int main() {
    int numFrames, numPages;
    printf("Enter the number of frames: ");
    scanf("%d", &numFrames);
    printf("Enter the number of pages: ");
    scanf("%d", &numPages);

    struct Page frames[MAX_FRAMES]; // Array to hold the frame contents
    struct Page pages[MAX_PAGES];   // Array to hold the page contents

    for (int i = 0; i < numFrames; i++) {
        frames[i].pageId = -1; // Initialize frames with an invalid page number
        frames[i].frequency = 0;
    }

    printf("Enter the page references: ");
    for (int i = 0; i < numPages; i++) {
        int pageId;
        scanf("%d", &pageId);

        // Check if the page is already in a frame
        bool pageFound = false;
        int pageFoundIndex = -1;
        for (int j = 0; j < numFrames; j++) {
            if (frames[j].pageId == pageId) {
                pageFound = true;
                pageFoundIndex = j;
                break;
            }
        }

        if (!pageFound) {
            if (numFrames > 0) {
                int lfuPageIndex = findLFUPage(frames, numFrames);
                frames[lfuPageIndex].pageId = pageId;
                frames[lfuPageIndex].frequency = 1;
            } else {
                // No frames available
                printf("No frames available to accommodate page %d\n", pageId);
            }
        } else {
            frames[pageFoundIndex].frequency++;
        }

        // Update the frequencies in the page array for future reference
        int pageArrayIndex = -1;
        for (int j = 0; j < numPages; j++) {
            if (pages[j].pageId == pageId) {
                pageArrayIndex = j;
                break;
            }
        }
        if (pageArrayIndex != -1) {
            pages[pageArrayIndex].frequency++;
        } else {
            pages[i].pageId = pageId;
            pages[i].frequency = 1;
        }

        // Print the current state of frames
        printf("Frames: ");
        for (int j = 0; j < numFrames; j++) {
            if (frames[j].pageId != -1) {
                printf("%d(%d) ", frames[j].pageId, frames[j].frequency);
            } else {
                printf("- ");
            }
        }
        printf("\n");
    }

    return 0;
}

