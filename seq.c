#include <stdio.h>
#include <stdlib.h>

#define MAX_FILES 10
#define MAX_BLOCKS 100

typedef struct {
    int startBlock;
    int length;
} FileAllocation;

FileAllocation files[MAX_FILES];
int allocatedBlocks[MAX_BLOCKS];

void initialize() {
    for (int i = 0; i < MAX_FILES; i++) {
        files[i].startBlock = -1;
        files[i].length = 0;
    }

    for (int i = 0; i < MAX_BLOCKS; i++) {
        allocatedBlocks[i] = 0;
    }
}

int allocateFile(int fileSize) {
    int startBlock = -1;

    for (int i = 0; i < MAX_BLOCKS; i++) {
        if (!allocatedBlocks[i]) {
            int contiguousBlocks = 0;
            for (int j = i; j < MAX_BLOCKS && !allocatedBlocks[j]; j++) {
                contiguousBlocks++;
                if (contiguousBlocks == fileSize) {
                    startBlock = i;
                    break;
                }
            }
            if (startBlock != -1) {
                break;
            }
        }
    }

    if (startBlock != -1) {
        for (int i = startBlock; i < startBlock + fileSize; i++) {
            allocatedBlocks[i] = 1;
        }
        return startBlock;
    } else {
        return -1;
    }
}

int main() {
    initialize();

    int numFiles;
    printf("Enter the number of files to allocate: ");
    scanf("%d", &numFiles);

    for (int i = 0; i < numFiles; i++) {
        int fileSize;
        printf("Enter the size of file %d: ", i + 1);
        scanf("%d", &fileSize);

        int startBlock = allocateFile(fileSize);
        if (startBlock != -1) {
            files[i].startBlock = startBlock;
            files[i].length = fileSize;
            printf("File %d allocated starting from block %d\n", i + 1, startBlock);
        } else {
            printf("File %d could not be allocated\n", i + 1);
        }
    }

    printf("File Allocation Table:\n");
    printf("File\tStart Block\tLength\n");
    for (int i = 0; i < MAX_FILES; i++) {
        if (files[i].length > 0) {
            printf("%d\t%d\t\t%d\n", i + 1, files[i].startBlock, files[i].length);
        }
    }

    return 0;
}

