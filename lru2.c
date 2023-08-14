#include <stdio.h>
#include <stdbool.h>

#define MAX_FRAMES 100

struct Stack {
    int items[MAX_FRAMES];
    int top;
};

void initializeStack(struct Stack *stack) {
    stack->top = -1;
}

void push(struct Stack *stack, int item) {
    if (stack->top < MAX_FRAMES - 1) {
        stack->items[++stack->top] = item;
    }
}

int pop(struct Stack *stack) {
    if (stack->top >= 0) {
        return stack->items[stack->top--];
    }
    return -1;
}

int main() {
    int numFrames, numPages;
    printf("Enter the number of frames: ");
    scanf("%d", &numFrames);
    printf("Enter the number of pages: ");
    scanf("%d", &numPages);

    int frames[MAX_FRAMES]; // Array to hold the frame contents
    struct Stack pageStack; // Stack to keep track of page order

    initializeStack(&pageStack);

    for (int i = 0; i < numFrames; i++) {
        frames[i] = -1; // Initialize frames with an invalid page number
    }

    printf("Enter the page references: ");
    for (int i = 0; i < numPages; i++) {
        int page;
        scanf("%d", &page);

        // Check if the page is already in a frame
        bool pageFound = false;
        int pageFoundIndex = -1;
        for (int j = 0; j < numFrames; j++) {
            if (frames[j] == page) {
                pageFound = true;
                pageFoundIndex = j;
                break;
            }
        }

        if (!pageFound) {
            if (pageStack.top == numFrames - 1) {
                // Remove the least recently used page from the stack
                int lruPage = pop(&pageStack);
                for (int j = 0; j < numFrames; j++) {
                    if (frames[j] == lruPage) {
                        frames[j] = page;
                        break;
                    }
                }
            } else {
                // Add the page to an empty frame
                frames[pageStack.top + 1] = page;
                push(&pageStack, page);
            }
        } else {
            // Update the page order in the stack
            int tempStack[MAX_FRAMES];
            int tempTop = -1;
            int poppedPage;
            while ((poppedPage = pop(&pageStack)) != -1) {
                if (poppedPage == page) {
                    break;
                }
                tempStack[++tempTop] = poppedPage;
            }
            while (tempTop >= 0) {
                push(&pageStack, tempStack[tempTop--]);
            }
            push(&pageStack, page);
        }

        // Print the current state of frames
        printf("Frames: ");
        for (int j = 0; j < numFrames; j++) {
            printf("%d ", frames[j]);
        }
        printf("\n");
    }

    return 0;
}

