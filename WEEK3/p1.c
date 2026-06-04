#include <stdio.h>

struct Process
{
    int at, bt, rt;
    int ct, wt, tat;
};

int main()
{
    int n, tq;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    for(int i = 0; i < n; i++)
    {
        printf("Enter Arrival Time and Burst Time for P%d: ", i + 1);
        scanf("%d %d", &p[i].at, &p[i].bt);
        p[i].rt = p[i].bt;
    }

    printf("Enter Time Quantum: ");
    scanf("%d", &tq);

    int queue[100], front = 0, rear = 0;
    int visited[100] = {0};

    int time = 0, completed = 0;

    queue[rear++] = 0;
    visited[0] = 1;

    while(completed < n)
    {
        int i = queue[front++];

        if(p[i].rt > tq)
        {
            time += tq;
            p[i].rt -= tq;
        }
        else
        {
            time += p[i].rt;
            p[i].rt = 0;

            p[i].ct = time;
            p[i].tat = p[i].ct - p[i].at;
            p[i].wt = p[i].tat - p[i].bt;

            completed++;
        }

        for(int j = 0; j < n; j++)
        {
            if(!visited[j] && p[j].at <= time)
            {
                queue[rear++] = j;
                visited[j] = 1;
            }
        }

        if(p[i].rt > 0)
            queue[rear++] = i;
    }

    float avgWT = 0, avgTAT = 0;

    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");

    for(int i = 0; i < n; i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               i + 1,
               p[i].at,
               p[i].bt,
               p[i].ct,
               p[i].tat,
               p[i].wt);

        avgWT += p[i].wt;
        avgTAT += p[i].tat;
    }

    printf("\nAverage Waiting Time = %.2f", avgWT / n);
    printf("\nAverage Turnaround Time = %.2f\n", avgTAT / n);

    return 0;
}
