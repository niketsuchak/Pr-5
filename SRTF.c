#include <stdio.h>

struct Process {
    int pid; // Process ID
    int burst_time; // Burst time of the process
    int remaining_time; // Remaining burst time of the process
};

void findWaitingTime(struct Process processes[], int n, int waiting_time[]) {
    int remaining_burst_time[n];
    for (int i = 0; i < n; i++) {
        remaining_burst_time[i] = processes[i].remaining_time;
    }

    int complete = 0;
    int t = 0;
    int min_remaining_time = INT_MAX;
    int shortest = 0;
    int finish_time;

    while (complete != n) {
        // Find the process with minimum remaining burst time at time t
        for (int j = 0; j < n; j++) {
            if ((processes[j].arrival_time <= t) && (remaining_burst_time[j] < min_remaining_time) && (remaining_burst_time[j] > 0)) {
                min_remaining_time = remaining_burst_time[j];
                shortest = j;
            }
        }

        // Reduce remaining burst time of the selected process
        remaining_burst_time[shortest]--;
        min_remaining_time = remaining_burst_time[shortest];
        if (min_remaining_time == 0) {
            min_remaining_time = INT_MAX;
        }

        // If a process is completed
        if (remaining_burst_time[shortest] == 0) {
            complete++;
            finish_time = t + 1;
            waiting_time[shortest] = finish_time - processes[shortest].burst_time;
        }

        t++;
    }
}

void findTurnaroundTime(struct Process processes[], int n, int waiting_time[], int turnaround_time[]) {
    for (int i = 0; i < n; i++) {
        turnaround_time[i] = processes[i].burst_time + waiting_time[i];
    }
}

void findAverageTime(struct Process processes[], int n) {
    int waiting_time[n], turnaround_time[n];

    // Function to find waiting time of all processes
    findWaitingTime(processes, n, waiting_time);

    // Function to find turnaround time for all processes
    findTurnaroundTime(processes, n, waiting_time, turnaround_time);

    // Calculate total waiting time and total turnaround time
    int total_waiting_time = 0, total_turnaround_time = 0;
    for (int i = 0; i < n; i++) {
        total_waiting_time += waiting_time[i];
        total_turnaround_time += turnaround_time[i];
    }

    // Calculate and print average waiting time and average turnaround time
    printf("Average waiting time = %.2f\n", (float)total_waiting_time / (float)n);
    printf("Average turnaround time = %.2f\n", (float)total_turnaround_time / (float)n);
}

int main() {
    struct Process processes[] = {{1, 6}, {2, 8}, {3, 7}, {4, 3}};
    int n = sizeof(processes) / sizeof(processes[0]);

    findAverageTime(processes, n);
    return 0;
}
