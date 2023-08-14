#include <stdio.h>
#include <stdlib.h>

#define MAX_BLOCKS 100

typedef struct BlockNode {
    int blockNumber;
    struct BlockNode* next;
} BlockNode;

typedef struct {
    BlockNode* startPointer;
    int length;
} FileAllocation;

FileAllocation files[MAX_BLOCKS];

void initialize() {
    for (int i = 0; i < MAX_BLOCKS; i++) {
        files[i].startPointer = NULL;
        files[i].length = 0;
    }
}

BlockNode* createBlockNode(int blockNumber) {
    BlockNode* newNode = (BlockNode*)malloc(sizeof(BlockNode));
    newNode->blockNumber = blockNumber;
    newNode->next = NULL;
    return newNode;
}

void allocateFile(int startBlock, int fileSize) {
    files[startBlock].startPointer = createBlockNode(startBlock);
    BlockNode* currentBlock = files[startBlock].startPointer;

    for (int i = 1; i < fileSize; i++) {
        int blockNumber = startBlock + i;
        currentBlock->next = createBlockNode(blockNumber);
        currentBlock = currentBlock->next;
    }

    files[startBlock].length = fileSize;
}

void accessFileBlocks(int startBlock) {
    if (files[startBlock].startPointer == NULL) {
        printf("File not allocated or has zero length.\n");
        return;
    }

    BlockNode* currentBlock = files[startBlock].startPointer;
    printf("Accessing blocks of file starting from block %d: ", startBlock);
    while (currentBlock != NULL) {
        printf("%d ", currentBlock->blockNumber);
        currentBlock = currentBlock->next;
    }
    printf("\n");
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

        allocateFile(startBlock, fileSize);
        printf("File %d allocated starting from block %d\n", i + 1, startBlock);
    }

    while (1) {
        int startBlock;
        printf("Enter the starting block of the file to access (or -1 to exit): ");
        scanf("%d", &startBlock);

        if (startBlock == -1) {
            break;
        }

        accessFileBlocks(startBlock);
    }

    return 0;
}

