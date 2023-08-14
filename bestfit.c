#include <stdio.h>

#define MAX_PARTITIONS 100

struct Partition {
    int size;
    int occupied; // 0 for free, 1 for occupied
};

void initializePartitions(struct Partition partitions[], int numPartitions) {
    for (int i = 0; i < numPartitions; i++) {
        partitions[i].occupied = 0; // Initialize all partitions as free
    }
}

int bestFit(struct Partition partitions[], int numPartitions, int processSize) {
    int bestIndex = -1;
    int bestSize = __INT_MAX__;

    for (int i = 0; i < numPartitions; i++) {
        if (partitions[i].occupied == 0 && partitions[i].size >= processSize) {
            if (partitions[i].size < bestSize) {
                bestSize = partitions[i].size;
                bestIndex = i;
            }
        }
    }

    if (bestIndex != -1) {
        partitions[bestIndex].occupied = 1;
    }

    return bestIndex;
}

int main() {
    struct Partition partitions[MAX_PARTITIONS];
    int numPartitions;

    printf("Enter the number of partitions: ");
    scanf("%d", &numPartitions);

    for (int i = 0; i < numPartitions; i++) {
        printf("Enter the size of partition %d: ", i + 1);
        scanf("%d", &partitions[i].size);
    }

    initializePartitions(partitions, numPartitions);

    int processSize;
    printf("Enter process size: ");
    scanf("%d", &processSize);

    int allocatedPartitionIndex = bestFit(partitions, numPartitions, processSize);

    if (allocatedPartitionIndex != -1) {
        printf("Process allocated in partition %d\n", allocatedPartitionIndex + 1);
    } else {
        printf("Process allocation failed - no suitable partition found\n");
    }

    return 0;
}

