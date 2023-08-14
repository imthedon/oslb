#include <stdio.h>
#include <stdlib.h>

#define MAX_BLOCKS 100

typedef struct {
    int startBlock;
    int length;
} FileAllocation;

typedef struct BlockNode {
    int blockNumber;
    struct BlockNode* next;
} BlockNode;

FileAllocation files[MAX_BLOCKS];
BlockNode* blockLists[MAX_BLOCKS];

void initialize() {
    for (int i = 0; i < MAX_BLOCKS; i++) {
        files[i].startBlock = -1;
        files[i].length = 0;
        blockLists[i] = NULL;
    }
}

BlockNode* createBlockNode(int blockNumber) {
    BlockNode* newNode = (BlockNode*)malloc(sizeof(BlockNode));
    newNode->blockNumber = blockNumber;
    newNode->next = NULL;
    return newNode;
}

int allocateFile(int fileSize) {
    int startBlock = -1;
    for (int i = 0; i < MAX_BLOCKS; i++) {
        if (files[i].length == 0) {
            startBlock = i;
            break;
        }
    }

    if (startBlock == -1) {
        return -1; // Allocation failed, no space available
    }

    files[startBlock].startBlock = startBlock;
    files[startBlock].length = fileSize;

    BlockNode* currentBlock = NULL;
    for (int i = 0; i < fileSize; i++) {
        int blockNumber = startBlock + i;
        BlockNode* newNode = createBlockNode(blockNumber);
        if (i == 0) {
            blockLists[startBlock] = newNode;
            currentBlock = newNode;
        } else {
            currentBlock->next = newNode;
            currentBlock = newNode;
        }
    }

    return startBlock;
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

    // Display block lists
    printf("Block Lists:\n");
    for (int i = 0; i < MAX_BLOCKS; i++) {
        if (blockLists[i] != NULL) {
            printf("File %d:", i + 1);
            BlockNode* currentBlock = blockLists[i];
            while (currentBlock != NULL) {
                printf(" -> %d", currentBlock->blockNumber);
                currentBlock = currentBlock->next;
            }
            printf("\n");
        }
    }

    return 0;
}

