/*
#include <stdio.h>

#define MEMORY_SIZE 1000 // Total available memory size

struct Partition {
    int start;
    int size;
    int occupied; // 0 for free, 1 for occupied
};

void initializePartitions(struct Partition partitions[], int numPartitions) {
    // Initialize the partitions with their sizes and set them as free
    // Initialize start, size, and occupied fields for each partition
}

int firstFit(struct Partition partitions[], int numPartitions, int processSize) {
    for (int i = 0; i < numPartitions; i++) {
        if (partitions[i].occupied == 0 && partitions[i].size >= processSize) {
            partitions[i].occupied = 1;
            return partitions[i].start;
        }
    }
    return -1; // No suitable partition found
}

int main() {
    struct Partition partitions[] = {
        {0, 200, 0}, // Example partitions: start, size, occupied
        {200, 300, 0},
        {500, 300, 0}
    };
    
    int numPartitions = sizeof(partitions) / sizeof(partitions[0]);
    
    // Initialize partitions
    
    int processSize;
    printf("Enter process size: ");
    scanf("%d", &processSize);
    
    int allocatedStart = firstFit(partitions, numPartitions, processSize);
    
    if (allocatedStart != -1) {
        printf("Process allocated in partition starting at %d\n", allocatedStart);
    } else {
        printf("Process allocation failed - no suitable partition found\n");
    }

    return 0;
}
*/



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

int firstFit(struct Partition partitions[], int numPartitions, int processSize) {
    for (int i = 0; i < numPartitions; i++) {
        if (partitions[i].occupied == 0 && partitions[i].size >= processSize) {
            partitions[i].occupied = 1;
            return i; // Return the index of the allocated partition
        }
    }
    return -1; // No suitable partition found
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

    int allocatedPartitionIndex = firstFit(partitions, numPartitions, processSize);

    if (allocatedPartitionIndex != -1) {
        printf("Process allocated in partition %d\n", allocatedPartitionIndex + 1);
    } else {
        printf("Process allocation failed - no suitable partition found\n");
    }

    return 0;
}


