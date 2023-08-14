#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 10

typedef struct {
    int id;
    int burst_time;
    int remaining_time;
    int arrival_time;
    int waiting_time;
    int turnaround_time;
} Process;

void initializeProcesses(Process processes[], int num_processes) {
    for (int i = 0; i < num_processes; i++) {
        processes[i].id = i + 1;
        printf("Enter arrival time for process P%d: ", processes[i].id);
        scanf("%d", &processes[i].arrival_time);
        printf("Enter burst time for process P%d: ", processes[i].id);
        scanf("%d", &processes[i].burst_time);
        processes[i].remaining_time = processes[i].burst_time;
        processes[i].waiting_time = 0;
        processes[i].turnaround_time = 0;
    }
}

void roundRobinScheduling(Process processes[], int num_processes, int time_quantum) {
    int total_time = 0;
    int total_waiting_time = 0;
    int total_turnaround_time = 0;
    int completed_processes = 0;

    while (completed_processes < num_processes) {
        for (int i = 0; i < num_processes; i++) {
            if (processes[i].remaining_time > 0) {
                int execution_time = (processes[i].remaining_time > time_quantum) ? time_quantum : processes[i].remaining_time;
                processes[i].remaining_time -= execution_time;
                total_time += execution_time;

                if (processes[i].remaining_time == 0) {
                    completed_processes++;
                    processes[i].turnaround_time = total_time - processes[i].arrival_time;
                }
            }
        }
    }

    for (int i = 0; i < num_processes; i++) {
        processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;
        total_waiting_time += processes[i].waiting_time;
        total_turnaround_time += processes[i].turnaround_time;
    }

    printf("Round Robin Scheduling completed.\n");
    printf("Total waiting time: %d units\n", total_waiting_time);
    printf("Average waiting time: %.2f units\n", (float)total_waiting_time / num_processes);
    printf("Total turnaround time: %d units\n", total_turnaround_time);
    printf("Average turnaround time: %.2f units\n", (float)total_turnaround_time / num_processes);
}

int main() {
    int num_processes;
    int time_quantum;

    printf("Enter the number of processes: ");
    scanf("%d", &num_processes);

    if (num_processes <= 0 || num_processes > MAX_PROCESSES) {
        printf("Invalid number of processes.\n");
        return 1;
    }

    Process processes[MAX_PROCESSES];
    initializeProcesses(processes, num_processes);

    printf("Enter the time quantum: ");
    scanf("%d", &time_quantum);

    roundRobinScheduling(processes, num_processes, time_quantum);

    return 0;
}

