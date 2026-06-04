#include <stdio.h>
#include <math.h>

#define MAX 10

typedef struct {
    int id;
    int bt; // Burst Time
    int deadline; // For EDF
    int period; // For RMS
    int ct, wt, tat;
} Process;

Process p[MAX], temp;
int n;

// ---------------- CPU UTILIZATION ----------------
float calculateUtilizationEDF() {
    float util = 0;
    for (int i = 0; i < n; i++) {
        util += (float)p[i].bt / p[i].deadline;
    }
    return util;
}

float calculateUtilizationRMS() {
    float util = 0;
    for (int i = 0; i < n; i++) {
        util += (float)p[i].bt / p[i].period;
    }
    return util;
}

// ---------------- EDF ----------------
void edfScheduling() {
    // Sort by deadline
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (p[i].deadline > p[j].deadline) {
                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }

    int time = 0;
    for (int i = 0; i < n; i++) {
        time += p[i].bt;
        p[i].ct = time;
        p[i].tat = p[i].ct;
        p[i].wt = p[i].tat - p[i].bt;
    }

    float util = calculateUtilizationEDF();

    printf("\n===== Earliest Deadline First (EDF) Scheduling =====\n");
    printf("CPU Utilization: %.2f\n", util);

    if (util <= 1)
        printf("Schedulable (Utilization <= 1)\n");
    else
        printf("Not Schedulable\n");

    printf("ID BT Deadline CT WT TAT\n");
    for (int i = 0; i < n; i++) {
        printf("%d %d %d %d %d %d\n",
               p[i].id, p[i].bt, p[i].deadline,
               p[i].ct, p[i].wt, p[i].tat);
    }
}

// ---------------- RMS ----------------
void rmsScheduling() {
    // Sort by period
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (p[i].period > p[j].period) {
                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }

    int time = 0;
    for (int i = 0; i < n; i++) {
        time += p[i].bt;
        p[i].ct = time;
        p[i].tat = p[i].ct;
        p[i].wt = p[i].tat - p[i].bt;
    }

    float util = calculateUtilizationRMS();
    float bound = n * (pow(2, (1.0 / n)) - 1);

    printf("\n===== Rate Monotonic Scheduling (RMS) =====\n");
    printf("CPU Utilization: %.2f\n", util);
    printf("RM Bound: %.4f\n", bound);

    if (util <= bound)
        printf("Schedulable (Utilization <= RM Bound)\n");
    else
        printf("Not Schedulable\n");

    printf("ID BT Period CT WT TAT\n");
    for (int i = 0; i < n; i++) {
        printf("%d %d %d %d %d %d\n",
               p[i].id, p[i].bt, p[i].period,
               p[i].ct, p[i].wt, p[i].tat);
    }
}

// ---------------- MAIN ----------------
int main() {
    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("\nEnter process details:\n");

    for (int i = 0; i < n; i++) {
        p[i].id = i;

        printf("\nProcess %d:\n", i);
        printf("Burst Time: ");
        scanf("%d", &p[i].bt);

        printf("Deadline (for EDF): ");
        scanf("%d", &p[i].deadline);

        printf("Period (for RMS): ");
        scanf("%d", &p[i].period);
    }

    edfScheduling();
    rmsScheduling();

    return 0;
