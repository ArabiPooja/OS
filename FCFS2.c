#include <stdio.h>

#define MAX 10

void fcfs(int n, int at[], int bt[]) {
    int ct[MAX];
    int tat[MAX];
    int wt[MAX];

    int total_wt = 0;
    int total_tat = 0;

    int current_time = 0;


    for (int i = 0; i < n; i++) {
        ct[i] = -1;
    }


    for (int i = 0; i < n; i++) {
        if (current_time < at[i]) {
            current_time = at[i];
        }

        ct[i] = current_time + bt[i];
        current_time = ct[i];
    }


    for (int i = 0; i < n; i++) {
        tat[i] = ct[i] - at[i];
        total_tat += tat[i];
    }

    for (int i = 0; i < n; i++) {
        wt[i] = tat[i] - bt[i];
        total_wt += wt[i];
    }


    printf("\nProcess\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", i+1, at[i], bt[i], ct[i], tat[i], wt[i]);
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

    fcfs(n, at, bt);

    return 0;
}
