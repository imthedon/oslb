#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 100

void fcfsDiskScheduling(int queue[], int head, int size) {
    int total_seek_time = 0;
    int current_track = head;

    printf("FCFS Disk Scheduling:\n");
    for (int i = 0; i < size; i++) {
        int seek_distance = abs(queue[i] - current_track);
        total_seek_time += seek_distance;
        printf("Move from %d to %d, Seek Time = %d\n", current_track - seek_distance, current_track, seek_distance);
        current_track = queue[i];
       //printf("Move from %d to %d, Seek Time = %d\n", current_track - seek_distance, current_track, seek_distance);
       
    }

    printf("Total Seek Time: %d\n", total_seek_time);
    printf("Average Seek Time: %.2f\n", (float) total_seek_time / size);
}

int main() {
    int queue[MAX_QUEUE_SIZE];
    int size, head;

    printf("Enter the size of the queue: ");
    scanf("%d", &size);

    if (size <= 0 || size > MAX_QUEUE_SIZE) {
        printf("Invalid queue size.\n");
        return 1;
    }

    printf("Enter the queue elements:\n");
    for (int i = 0; i < size; i++) {
        scanf("%d", &queue[i]);
    }

    printf("Enter the initial head position: ");
    scanf("%d", &head);

    fcfsDiskScheduling(queue, head, size);

    return 0;
}

