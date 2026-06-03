#include <stdio.h>

#define MAX 10

struct Task {
    int id;
    int execution;
    int period;
    int remaining;
    int deadline;
};

void RMS(struct Task t[], int n, int timeLimit) {
    printf("\nRate Monotonic Scheduling:\n");

    for (int time = 0; time < timeLimit; time++) {

        for (int i = 0; i < n; i++) {
            if (time % t[i].period == 0)
                t[i].remaining = t[i].execution;
        }

        int selected = -1;

        for (int i = 0; i < n; i++) {
            if (t[i].remaining > 0) {
                if (selected == -1 ||
                    t[i].period < t[selected].period)
                    selected = i;
            }
        }

        if (selected != -1) {
            printf("Time %d : Task %d\n",
                   time, t[selected].id);
            t[selected].remaining--;
        }
        else {
            printf("Time %d : Idle\n", time);
        }
    }
}

void EDF(struct Task t[], int n, int timeLimit) {
    printf("\nEarliest Deadline First Scheduling:\n");

    for (int time = 0; time < timeLimit; time++) {

        for (int i = 0; i < n; i++) {
            if (time % t[i].period == 0) {
                t[i].remaining = t[i].execution;
                t[i].deadline = time + t[i].period;
            }
        }

        int selected = -1;

        for (int i = 0; i < n; i++) {
            if (t[i].remaining > 0) {
                if (selected == -1 ||
                    t[i].deadline < t[selected].deadline)
                    selected = i;
            }
        }

        if (selected != -1) {
            printf("Time %d : Task %d\n",
                   time, t[selected].id);
            t[selected].remaining--;
        }
        else {
            printf("Time %d : Idle\n", time);
        }
    }
}

int main() {
    int n, timeLimit;

    printf("Enter number of tasks: ");
    scanf("%d", &n);

    struct Task t[MAX], temp[MAX];

    for (int i = 0; i < n; i++) {
        t[i].id = i + 1;

        printf("\nTask %d\n", i + 1);

        printf("Execution Time: ");
        scanf("%d", &t[i].execution);

        printf("Period: ");
        scanf("%d", &t[i].period);

        t[i].remaining = t[i].execution;
        t[i].deadline = t[i].period;

        temp[i] = t[i];
    }

    printf("\nEnter simulation time: ");
    scanf("%d", &timeLimit);

    RMS(t, n, timeLimit);

    for (int i = 0; i < n; i++)
        t[i] = temp[i];

    EDF(t, n, timeLimit);

    return 0;
}
