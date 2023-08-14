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

int worstFit(struct Partition partitions[], int numPartitions, int processSize) {
    int worstIndex = -1;
    int worstSize = -1;

    for (int i = 0; i < numPartitions; i++) {
        if (partitions[i].occupied == 0 && partitions[i].size >= processSize) {
            if (partitions[i].size > worstSize) {
                worstSize = partitions[i].size;
                worstIndex = i;
            }
        }
    }

    if (worstIndex != -1) {
        partitions[worstIndex].occupied = 1;
    }

    return worstIndex;
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

    int allocatedPartitionIndex = worstFit(partitions, numPartitions, processSize);

    if (allocatedPartitionIndex != -1) {
        printf("Process allocated in partition %d\n", allocatedPartitionIndex + 1);
    } else {
        printf("Process allocation failed - no suitable partition found\n");
    }

    return 0;
}

