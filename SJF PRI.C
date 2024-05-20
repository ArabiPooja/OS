#include <stdio.h>

#define MAX 10

void sjf_non_preemptive(int n, int at[], int bt[]) {
    int ct[MAX];
    int tat[MAX];
    int wt[MAX];
    int rt[MAX]; // Remaining time

    int total_wt = 0;
    int total_tat = 0;
    int completed = 0;
    int current_time = 0;
    int shortest_job = 0;
    int min_bt = 9999; // A very large number initially
    int is_completed[MAX] = {0}; // To keep track of completed processes

    // Initialize remaining times
    for (int i = 0; i < n; i++) {
        rt[i] = bt[i];
    }

    while (completed < n) {
        for (int i = 0; i < n; i++) {
            if (at[i] <= current_time && rt[i] < min_bt && !is_completed[i]) {
                shortest_job = i;
                min_bt = rt[i];
            }
        }

        rt[shortest_job]--;

        if (rt[shortest_job] == 0) {
            completed++;
            min_bt = 9999;
            is_completed[shortest_job] = 1;

            ct[shortest_job] = current_time + 1;

            tat[shortest_job] = ct[shortest_job] - at[shortest_job];
            total_tat += tat[shortest_job];

            wt[shortest_job] = tat[shortest_job] - bt[shortest_job];
            if (wt[shortest_job] < 0) wt[shortest_job] = 0;
            total_wt += wt[shortest_job];
        }

        current_time++;
    }

    printf("\nProcess\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", i + 1, at[i], bt[i], ct[i], tat[i], wt[i]);
    }

    printf("\nAverage waiting time: %.2f", (float)total_wt / n);
    printf("\nAverage turnaround time: %.2f", (float)total_tat / n);
}

int main() {
    int n, i;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int at[n], bt[n];

    printf("Enter the arrival time:\n");
    for (i = 0; i < n; i++) {
        scanf("%d", &at[i]);
    }

    printf("Enter the burst time:\n");
    for (i = 0; i < n; i++) {
        scanf("%d", &bt[i]);
    }

    sjf_non_preemptive(n, at, bt);

    return 0;
}
