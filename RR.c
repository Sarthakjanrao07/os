#include <stdio.h>
#define MAX_PROCESSES 10

// Function to input process details (arrival time and burst time)
void inputProcessDetails(int n, int burst_time[], int arrival_time[]) {
    for (int i = 0; i < n; i++) {
        printf("Burst time for process %d: ", i + 1);
        scanf("%d", &burst_time[i]);
        printf("Arrival time for process %d: ", i + 1);
        scanf("%d", &arrival_time[i]);
    }
}

// Function to perform Round Robin scheduling and calculate waiting and turnaround times
void roundRobinScheduling(int n, int burst_time[], int arrival_time[], int time_quantum,
                          int waiting_time[], int turnaround_time[]) {
    int remaining_time[MAX_PROCESSES];
    int completed = 0, current_time = 0;

    // Copy burst times to remaining time
    for (int i = 0; i < n; i++) {
        remaining_time[i] = burst_time[i];
    }

    // Main loop to simulate Round Robin scheduling
    while (completed < n) {
        for (int i = 0; i < n; i++) {
            // Process only if it has arrived and still has remaining burst time
            if (arrival_time[i] <= current_time && remaining_time[i] > 0) {
                if (remaining_time[i] <= time_quantum) {
                    // Process the remaining time and set to 0 (completed)
                    current_time += remaining_time[i];
                    remaining_time[i] = 0;
                    completed++;

                    // Calculate turnaround time and waiting time
                    turnaround_time[i] = current_time - arrival_time[i];
                    waiting_time[i] = turnaround_time[i] - burst_time[i];
                } else {
                    // Process for time quantum and reduce remaining time
                    current_time += time_quantum;
                    remaining_time[i] -= time_quantum;
                }
            }
        }
    }
}

// Function to calculate average waiting time and turnaround time
void calculateAverages(int n, int waiting_time[], int turnaround_time[], double* avg_waiting_time, double* avg_turnaround_time) {
    *avg_waiting_time = 0;
    *avg_turnaround_time = 0;

    for (int i = 0; i < n; i++) {
        *avg_waiting_time += waiting_time[i];
        *avg_turnaround_time += turnaround_time[i];
    }

    *avg_waiting_time /= n;
    *avg_turnaround_time /= n;
}

// Function to display the results in a formatted table
void displayResults(int n, int burst_time[], int arrival_time[], int waiting_time[], int turnaround_time[]) {
    printf("\nProcess\tBurst Time\tArrival Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\t\t%d\t\t%d\n", i + 1, burst_time[i], arrival_time[i], waiting_time[i], turnaround_time[i]);
    }
}

int main() {
    int n, time_quantum;
    int burst_time[MAX_PROCESSES], arrival_time[MAX_PROCESSES];
    int waiting_time[MAX_PROCESSES], turnaround_time[MAX_PROCESSES];

    // Input the number of processes and time quantum
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    printf("Enter time quantum: ");
    scanf("%d", &time_quantum);

    // Input burst times and arrival times for each process
    inputProcessDetails(n, burst_time, arrival_time);

    // Perform Round Robin Scheduling
    roundRobinScheduling(n, burst_time, arrival_time, time_quantum, waiting_time, turnaround_time);

    // Calculate averages
    double avg_waiting_time, avg_turnaround_time;
    calculateAverages(n, waiting_time, turnaround_time, &avg_waiting_time, &avg_turnaround_time);

    // Display the results
    displayResults(n, burst_time, arrival_time, waiting_time, turnaround_time);

    // Display average times
    printf("\nAverage Waiting Time: %.2f\n", avg_waiting_time);
    printf("Average Turnaround Time: %.2f\n", avg_turnaround_time);

    return 0;
}
