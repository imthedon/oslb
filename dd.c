#include <stdio.h>

#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

int processesCount, resourcesCount;
int allocation[MAX_PROCESSES][MAX_RESOURCES];
int maxDemand[MAX_PROCESSES][MAX_RESOURCES];
int available[MAX_RESOURCES];
int marked[MAX_PROCESSES];

void initialize() {
    for (int i = 0; i < processesCount; i++) {
        marked[i] = 0;
        for (int j = 0; j < resourcesCount; j++) {
            allocation[i][j] = 0;
            maxDemand[i][j] = 0;
        }
    }
}

int requestIsSafe(int process, int request[]) {
    for (int i = 0; i < resourcesCount; i++) {
        if (request[i] > available[i])
            return 0;
        if (request[i] > maxDemand[process][i])
            return 0;
    }
    return 1;
}

int detectDeadlock() {
    int work[MAX_RESOURCES];
    int finish[MAX_PROCESSES];
    int found, safeSequence[MAX_PROCESSES], count = 0;

    for (int i = 0; i < resourcesCount; i++) {
        work[i] = available[i];
    }

    for (int i = 0; i < processesCount; i++) {
        finish[i] = 0;
    }

    while (count < processesCount) {
        found = 0;
        for (int i = 0; i < processesCount; i++) {
            if (!finish[i] && requestIsSafe(i, maxDemand[i])) {
                for (int j = 0; j < resourcesCount; j++) {
                    work[j] += allocation[i][j];
                }
                finish[i] = 1;
                safeSequence[count++] = i;
                found = 1;
            }
        }

        if (!found) {
            for (int i = 0; i < processesCount; i++) {
                if (!finish[i] && marked[i] == 0) {
                    marked[i] = 1;
                    break;
                }
            }
        }
    }

    printf("Safe Sequence: ");
    for (int i = 0; i < count; i++) {
        printf("%d ", safeSequence[i]);
    }
    printf("\n");

    return count == processesCount ? 0 : 1;
}

int main() {
    printf("Enter the number of processes: ");
    scanf("%d", &processesCount);

    printf("Enter the number of resources: ");
    scanf("%d", &resourcesCount);

    printf("Enter the available resources: ");
    for (int i = 0; i < resourcesCount; i++) {
        scanf("%d", &available[i]);
    }

    printf("Enter the allocation matrix:\n");
    for (int i = 0; i < processesCount; i++) {
        for (int j = 0; j < resourcesCount; j++) {
            scanf("%d", &allocation[i][j]);
        }
    }

    printf("Enter the max demand matrix:\n");
    for (int i = 0; i < processesCount; i++) {
        for (int j = 0; j < resourcesCount; j++) {
            scanf("%d", &maxDemand[i][j]);
        }
    }

    int deadlockDetected = detectDeadlock();
    if (deadlockDetected) {
        printf("Deadlock Detected!\n");
    } else {
        printf("No Deadlock Detected.\n");
    }

    // Request resources for deadlock detection
    printf("Enter process index for resource request: ");
    int processIndex;
    scanf("%d", &processIndex);

    printf("Enter resource request for process %d: ", processIndex);
    int request[MAX_RESOURCES];
    for (int i = 0; i < resourcesCount; i++) {
        scanf("%d", &request[i]);
    }

    if (requestIsSafe(processIndex, request)) {
        for (int i = 0; i < resourcesCount; i++) {
            allocation[processIndex][i] += request[i];
            available[i] -= request[i];
        }
        printf("Resource request granted.\n");
        int newDeadlockDetected = detectDeadlock();
        if (newDeadlockDetected) {
            printf("Deadlock Detected!\n");
        } else {
            printf("No Deadlock Detected.\n");
        }
    } else {
        printf("Resource request denied.\n");
    }

    return 0;
}

