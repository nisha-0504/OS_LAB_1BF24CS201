#include <stdio.h>

#define MAX 25

void firstFit(int blockSize[], int m, int processSize[], int n) {
    int allocation[MAX];
    int temp[MAX];

    for (int i = 0; i < m; i++)
        temp[i] = blockSize[i];

    for (int i = 0; i < n; i++)
        allocation[i] = -1;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (temp[j] >= processSize[i]) {
                allocation[i] = j;
                temp[j] -= processSize[i];
                break;
            }
        }
    }

    printf("\n--- First Fit ---\n");
    printf("Process No.\tProcess Size\tBlock No.\n");

    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t", i + 1, processSize[i]);

        if (allocation[i] != -1)
            printf("%d\n", allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }
}

void bestFit(int blockSize[], int m, int processSize[], int n) {
    int allocation[MAX];
    int temp[MAX];

    for (int i = 0; i < m; i++)
        temp[i] = blockSize[i];

    for (int i = 0; i < n; i++)
        allocation[i] = -1;

    for (int i = 0; i < n; i++) {
        int bestIdx = -1;

        for (int j = 0; j < m; j++) {
            if (temp[j] >= processSize[i]) {
                if (bestIdx == -1 || temp[j] < temp[bestIdx]) {
                    bestIdx = j;
                }
            }
        }

        if (bestIdx != -1) {
            allocation[i] = bestIdx;
            temp[bestIdx] -= processSize[i];
        }
    }

    printf("\n--- Best Fit ---\n");
    printf("Process No.\tProcess Size\tBlock No.\n");

    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t", i + 1, processSize[i]);

        if (allocation[i] != -1)
            printf("%d\n", allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }
}

void worstFit(int blockSize[], int m, int processSize[], int n) {
    int allocation[MAX];
    int temp[MAX];

    for (int i = 0; i < m; i++)
        temp[i] = blockSize[i];

    for (int i = 0; i < n; i++)
        allocation[i] = -1;

    for (int i = 0; i < n; i++) {
        int worstIdx = -1;

        for (int j = 0; j < m; j++) {
            if (temp[j] >= processSize[i]) {
                if (worstIdx == -1 || temp[j] > temp[worstIdx]) {
                    worstIdx = j;
                }
            }
        }

        if (worstIdx != -1) {
            allocation[i] = worstIdx;
            temp[worstIdx] -= processSize[i];
        }
    }

    printf("\n--- Worst Fit ---\n");
    printf("Process No.\tProcess Size\tBlock No.\n");

    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t", i + 1, processSize[i]);

        if (allocation[i] != -1)
            printf("%d\n", allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }
}

int main() {
    int blockSize[MAX], processSize[MAX];
    int m, n;

    printf("Enter number of memory blocks: ");
    scanf("%d", &m);

    printf("Enter sizes of %d memory blocks:\n", m);
    for (int i = 0; i < m; i++) {
        scanf("%d", &blockSize[i]);
    }

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter sizes of %d processes:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &processSize[i]);
    }

    firstFit(blockSize, m, processSize, n);
    bestFit(blockSize, m, processSize, n);
    worstFit(blockSize, m, processSize, n);

    return 0;
}
