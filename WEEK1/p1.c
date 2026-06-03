#include <stdio.h>

int main() {
    int n, i, choice;
    int at[10], bt[10], ct[10], tat[10], wt[10];

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for(i = 0; i < n; i++) {
        printf("Enter AT and BT for P%d: ", i+1);
        scanf("%d %d", &at[i], &bt[i]);
    }

    printf("\nSelect Type:\n");
    printf("1. Non-Preemptive\n");
    printf("2. Preemptive\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    if(choice == 1) {
        // FCFS Scheduling
        ct[0] = at[0] + bt[0];

        for(i = 1; i < n; i++) {
            if(ct[i-1] < at[i])
                ct[i] = at[i] + bt[i];
            else
                ct[i] = ct[i-1] + bt[i];
        }

        for(i = 0; i < n; i++) {
            tat[i] = ct[i] - at[i];
            wt[i] = tat[i] - bt[i];
        }

        printf("\nP\tAT\tBT\tCT\tTAT\tWT\n");
        for(i = 0; i < n; i++) {
            printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
            i+1, at[i], bt[i], ct[i], tat[i], wt[i]);
        }
    }
    else {
        printf("FCFS does not support Preemptive scheduling\n");
    }

    return 0;
}
