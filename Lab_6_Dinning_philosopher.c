#include <stdio.h>
#include <stdlib.h>

#define N 5  // Total number of philosophers
#define HUNGRY_COUNT 3  // Number of hungry philosophers

void one_eat_at_a_time(int *hungry_positions) {
    printf("\nAllow one philosopher to eat at any time\n");
    for (int i = 0; i < HUNGRY_COUNT; i++) {
        printf("P%d is granted to eat\n", hungry_positions[i]);
        for (int j = 0; j < HUNGRY_COUNT; j++) {
            if (j != i) {
                printf("P%d is waiting\n", hungry_positions[j]);
            }
        }
    }
}

void two_eat_at_a_time(int *hungry_positions) {
    printf("\nAllow two philosophers to eat at same time\n");
    int combinations[3][2] = {
        {hungry_positions[0], hungry_positions[1]},
        {hungry_positions[0], hungry_positions[2]},
        {hungry_positions[1], hungry_positions[2]}
    };

    for (int i = 0; i < 3; i++) {
        printf("Combination %d\n", i + 1);
        printf("P%d and P%d are granted to eat\n", combinations[i][0], combinations[i][1]);
        for (int j = 0; j < HUNGRY_COUNT; j++) {
            if (hungry_positions[j] != combinations[i][0] && hungry_positions[j] != combinations[i][1]) {
                printf("P%d is waiting\n", hungry_positions[j]);
            }
        }
    }
}

int main() {
    int total_philosophers;
    int hungry_count;
    int hungry_positions[HUNGRY_COUNT];
    int choice;

    printf("DINING PHILOSOPHER PROBLEM\n");
    printf("Enter the total no. of philosophers: ");
    scanf("%d", &total_philosophers);
    printf("How many are hungry: ");
    scanf("%d", &hungry_count);

    for (int i = 0; i < hungry_count; i++) {
        printf("Enter philosopher %d position: ", i + 1);
        scanf("%d", &hungry_positions[i]);
    }

    while (1) {
        printf("\n1. One can eat at a time  2. Two can eat at a time  3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 3) {
            exit(0);
        } else if (choice == 1) {
            one_eat_at_a_time(hungry_positions);
        } else if (choice == 2) {
            two_eat_at_a_time(hungry_positions);
        } else {
            printf("Invalid choice, please enter 1, 2, or 3.\n");
        }
    }

    return 0;
}
