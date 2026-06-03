#include <stdio.h>
#define MAX 100

int main() {
    int n, q_count;
    int at[MAX], bt[MAX], rt[MAX];
    int ct[MAX], tat[MAX], wt[MAX];
    int queue[MAX], visited[MAX];
    int front, rear, time, completed;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter Arrival Time and Burst Time:\n");
    for (int i = 0; i < n; i++) {
        printf("P%d AT BT: ", i + 1);
        scanf("%d %d", &at[i], &bt[i]);
    }
    printf("\nEnter number of quantum values: ");
    scanf("%d", &q_count);
    int quantum[q_count];
    printf("Enter quantum values:\n");
    for (int i = 0; i < q_count; i++) {
        scanf("%d", &quantum[i]);
    }
    for (int q = 0; q < q_count; q++) {
        for (int i = 0; i < n; i++) {
            rt[i] = bt[i];
            visited[i] = 0;
        }
        front = rear = 0;
        time = 0;
        completed = 0;
        queue[rear++] = 0;
        visited[0] = 1;
        while (completed < n) {
            if (front == rear)
                break;
            int i = queue[front++];
            if (rt[i] > quantum[q]) {
                time += quantum[q];
                rt[i] -= quantum[q];
            }
            else {
                time += rt[i];
                rt[i] = 0;
                ct[i] = time;
                completed++;
            }
            for (int j = 0; j < n; j++) {
                if (!visited[j] && at[j] <= time) {
                    queue[rear++] = j;
                    visited[j] = 1;
                }
            }
            if (rt[i] > 0)
                queue[rear++] = i;
            if (front == rear) {
                for (int j = 0; j < n; j++) {
                    if (rt[j] > 0) {
                        queue[rear++] = j;
                        visited[j] = 1;
                        time = at[j];
                        break;
                    }
                }
            }
        }
        float total_tat = 0, total_wt = 0;
        printf("\nQuantum = %d\n", quantum[q]);
        printf("PID\tAT\tBT\tCT\tTAT\tWT\n");
        for (int i = 0; i < n; i++) {
            tat[i] = ct[i] - at[i];
            wt[i] = tat[i] - bt[i];
            total_tat += tat[i];
            total_wt += wt[i];
            printf("P%d\t%d\t%d\t%d\t%d\t%d\n",i + 1, at[i], bt[i], ct[i], tat[i], wt[i]);
        }
        printf("Average TAT = %.2f\n", total_tat / n);
        printf("Average WT  = %.2f\n", total_wt / n);
    }
    return 0;
}
