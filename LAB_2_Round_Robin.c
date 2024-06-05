#include <stdio.h>
#define MAX 10
void round_robin(int n, int bt[], int quantum) {
    int wt[MAX] = {0};
    int tat[MAX] = {0};
    int remaining_bt[MAX];
    int total_wt = 0, total_tat = 0;
    int time = 0;
    for (int i = 0; i < n; i++) {
        remaining_bt[i] = bt[i];
    }
    while (1) {
        int done = 1;
        for (int i = 0; i < n; i++) {
            if (remaining_bt[i] > 0) {
                done = 0;
                if (remaining_bt[i] > quantum) {
                    time += quantum;
                    remaining_bt[i] -= quantum;
                } else {
                    time += remaining_bt[i];
                    wt[i] = time - bt[i];
                    remaining_bt[i] = 0;
                }
            }
        }

        if (done == 1) break;
    }
    for (int i = 0; i < n; i++) {
        tat[i] = bt[i] + wt[i];
        total_wt += wt[i];
        total_tat += tat[i];
    }
    printf("\nProcess\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\n", i + 1, bt[i], wt[i], tat[i]);
    }

    printf("\nAverage waiting time: %.2f", (float)total_wt / n);
    printf("\nAverage turnaround time: %.2f", (float)total_tat / n);
}

int main() {
    int n, quantum;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int bt[MAX];

    printf("Enter Burst Time for each process:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d: ", i + 1);
        scanf("%d", &bt[i]);
    }

    printf("Enter the size of time slice (quantum): ");
    scanf("%d", &quantum);

    round_robin(n, bt, quantum);

    return 0;
}
