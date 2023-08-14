#include <stdio.h>

struct Process {
    int pid;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int waiting_time;
    int turnaround_time;
};

void calculateTimes(struct Process processes[], int n) {
    int total_waiting_time = 0;
    int total_turnaround_time = 0;
    int current_time = 0;
    int completed = 0;

    while (completed < n) {
        int min_remaining_time = __INT_MAX__;
        int shortest_process = -1;

        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= current_time && processes[i].remaining_time < min_remaining_time && processes[i].remaining_time > 0) {
                min_remaining_time = processes[i].remaining_time;
                shortest_process = i;
            }
        }

        if (shortest_process == -1) {
            current_time++;
            continue;
        }

        processes[shortest_process].remaining_time--;
        current_time++;

        if (processes[shortest_process].remaining_time == 0) {
            completed++;
            processes[shortest_process].waiting_time = current_time - processes[shortest_process].arrival_time - processes[shortest_process].burst_time;
            processes[shortest_process].turnaround_time = current_time - processes[shortest_process].arrival_time;
            total_waiting_time += processes[shortest_process].waiting_time;
            total_turnaround_time += processes[shortest_process].turnaround_time;
        }
    }

    double average_waiting_time = (double) total_waiting_time / n;
    double average_turnaround_time = (double) total_turnaround_time / n;

    printf("Process\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].pid, processes[i].arrival_time, processes[i].burst_time, processes[i].waiting_time, processes[i].turnaround_time);
    }

    printf("Average Waiting Time: %.2lf\n", average_waiting_time);
    printf("Average Turnaround Time: %.2lf\n", average_turnaround_time);
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    
    struct Process processes[n];
    
    for (int i = 0; i < n; i++) {
        printf("Enter arrival time and burst time for process %d: ", i + 1);
        scanf("%d %d", &processes[i].arrival_time, &processes[i].burst_time);
        processes[i].pid = i + 1;
        processes[i].remaining_time = processes[i].burst_time;
        processes[i].waiting_time = 0;
        processes[i].turnaround_time = 0;
    }

    calculateTimes(processes, n);
    
    return 0;
}

