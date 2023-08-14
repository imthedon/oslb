#include <stdio.h>
#include <stdlib.h>

#define MAX_BLOCKS 100

typedef struct {
    int startBlock;
    int length;
} FileAllocation;

FileAllocation files[MAX_BLOCKS];
int allocatedBlocks[MAX_BLOCKS];

void initialize() {
    for (int i = 0; i < MAX_BLOCKS; i++) {
        allocatedBlocks[i] = 0;
        files[i].startBlock = -1;
        files[i].length = 0;
    }
}

int allocateFile(int startBlock, int fileSize) {
    if (allocatedBlocks[startBlock] || startBlock + fileSize > MAX_BLOCKS) {
        return 0; // Allocation failed
    }

    for (int i = startBlock; i < startBlock + fileSize; i++) {
        if (allocatedBlocks[i]) {
            return 0; // Allocation failed
        }
    }

    for (int i = startBlock; i < startBlock + fileSize; i++) {
        allocatedBlocks[i] = 1;
    }

    return 1; // Allocation successful
}

int main() {
    initialize();

    int numFiles;
    printf("Enter the number of files to allocate: ");
    scanf("%d", &numFiles);

    for (int i = 0; i < numFiles; i++) {
        int startBlock, fileSize;
        printf("Enter the starting block for file %d: ", i + 1);
        scanf("%d", &startBlock);
        printf("Enter the size of file %d: ", i + 1);
        scanf("%d", &fileSize);

        if (allocateFile(startBlock, fileSize)) {
            files[i].startBlock = startBlock;
            files[i].length = fileSize;
            printf("File %d allocated starting from block %d\n", i + 1, startBlock);
        } else {
            printf("File %d could not be allocated\n", i + 1);
        }
    }

    printf("File Allocation Table:\n");
    printf("File\tStart Block\tLength\n");
    for (int i = 0; i < MAX_BLOCKS; i++) {
        if (files[i].length > 0) {
            printf("%d\t%d\t\t%d\n", i + 1, files[i].startBlock, files[i].length);
        }
    }

    return 0;
}

