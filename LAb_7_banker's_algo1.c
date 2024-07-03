#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

// Function declarations
bool isSafeState(int processes, int resources, int available[], int max[][MAX_RESOURCES], int allocation[][MAX_RESOURCES], int need[][MAX_RESOURCES], int safeSequence[]);
void calculateNeed(int processes, int resources, int max[][MAX_RESOURCES], int allocation[][MAX_RESOURCES], int need[][MAX_RESOURCES]);
bool requestResources(int processes, int resources, int available[], int max[][MAX_RESOURCES], int allocation[][MAX_RESOURCES], int need[][MAX_RESOURCES], int processID, int request[]);

int main() {
    int processes, resources;
    int available[MAX_RESOURCES];
    int max[MAX_PROCESSES][MAX_RESOURCES];
    int allocation[MAX_PROCESSES][MAX_RESOURCES];
    int need[MAX_PROCESSES][MAX_RESOURCES];
    int safeSequence[MAX_PROCESSES];

    printf("Enter the number of processes: ");
    scanf("%d", &processes);

    printf("Enter the number of resources: ");
    scanf("%d", &resources);

    printf("Enter the available resources:\n");
    for (int i = 0; i < resources; i++) {
        scanf("%d", &available[i]);
    }

    printf("Enter the maximum resource matrix:\n");
    for (int i = 0; i < processes; i++) {
        printf("Enter details for P%d\n", i);
        for (int j = 0; j < resources; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    printf("Enter the allocation resource matrix:\n");
    for (int i = 0; i < processes; i++) {
        for (int j = 0; j < resources; j++) {
            scanf("%d", &allocation[i][j]);
        }
    }

    // Calculate the need matrix
    calculateNeed(processes, resources, max, allocation, need);

    int processID, request[MAX_RESOURCES];
    printf("Enter New Request Details --\n");
    printf("Enter pid: ");
    scanf("%d", &processID);
    printf("Enter Request for Resources: ");
    for (int i = 0; i < resources; i++) {
        scanf("%d", &request[i]);
    }

    if (requestResources(processes, resources, available, max, allocation, need, processID, request)) {
        printf("Request can be granted.\n");
    } else {
        printf("Request cannot be granted.\n");
    }

    if (isSafeState(processes, resources, available, max, allocation, need, safeSequence)) {
        printf("SYSTEM IS IN SAFE STATE\n");
        printf("The Safe Sequence is -- (");
        for (int i = 0; i < processes; i++) {
            printf("P%d ", safeSequence[i]);
        }
        printf(")\n");
    } else {
        printf("SYSTEM IS NOT IN SAFE STATE\n");
    }

    printf("\nProcess\tAllocation\t\tMax\t\tNeed\n");
    for (int i = 0; i < processes; i++) {
        printf("P%d\t", i);
        for (int j = 0; j < resources; j++) {
            printf("%d ", allocation[i][j]);
        }
        printf("\t");
        for (int j = 0; j < resources; j++) {
            printf("%d ", max[i][j]);
        }
        printf("\t");
        for (int j = 0; j < resources; j++) {
            printf("%d ", need[i][j]);
        }
        printf("\n");
    }

    return 0;
}

void calculateNeed(int processes, int resources, int max[][MAX_RESOURCES], int allocation[][MAX_RESOURCES], int need[][MAX_RESOURCES]) {
    for (int i = 0; i < processes; i++) {
        for (int j = 0; j < resources; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
}

bool isSafeState(int processes, int resources, int available[], int max[][MAX_RESOURCES], int allocation[][MAX_RESOURCES], int need[][MAX_RESOURCES], int safeSequence[]) {
    int work[MAX_RESOURCES];
    bool finish[MAX_PROCESSES] = {false};
    int count = 0;

    // Initialize work to available resources
    for (int i = 0; i < resources; i++) {
        work[i] = available[i];
    }

    // Finding an index i such that finish[i] is false and need[i] <= work
    while (count < processes) {
        bool found = false;
        for (int i = 0; i < processes; i++) {
            if (!finish[i]) {
                bool canAllocate = true;
                for (int j = 0; j < resources; j++) {
                    if (need[i][j] > work[j]) {
                        canAllocate = false;
                        break;
                    }
                }

                if (canAllocate) {
                    // Simulate allocation to process i
                    for (int j = 0; j < resources; j++) {
                        work[j] += allocation[i][j];
                    }
                    finish[i] = true;
                    safeSequence[count++] = i;
                    found = true;
                    printf("P%d is visited (", i);
                    for (int j = 0; j < resources; j++) {
                        printf("%d ", work[j]);
                    }
                    printf(")\n");
                }
            }
        }

        if (!found) {
            // If no process could be allocated, check if all processes are finished
            for (int i = 0; i < processes; i++) {
                if (!finish[i]) {
                    return false;
                }
            }
            return true;
        }
    }
    return true;
}

bool requestResources(int processes, int resources, int available[], int max[][MAX_RESOURCES], int allocation[][MAX_RESOURCES], int need[][MAX_RESOURCES], int processID, int request[]) {
    // Check if request is greater than need
    for (int i = 0; i < resources; i++) {
        if (request[i] > need[processID][i]) {
            return false;
        }
    }

    // Check if request is greater than available
    for (int i = 0; i < resources; i++) {
        if (request[i] > available[i]) {
            return false;
        }
    }

    // Pretend to allocate the requested resources
    for (int i = 0; i < resources; i++) {
        available[i] -= request[i];
        allocation[processID][i] += request[i];
        need[processID][i] -= request[i];
    }

    // Check if the system is still in a safe state
    int safeSequence[MAX_PROCESSES];
    if (isSafeState(processes, resources, available, max, allocation, need, safeSequence)) {
        return true;
    } else {
        // Rollback the pretend allocation
        for (int i = 0; i < resources; i++) {
            available[i] += request[i];
            allocation[processID][i] -= request[i];
            need[processID][i] += request[i];
        }
        return false;
    }
}
