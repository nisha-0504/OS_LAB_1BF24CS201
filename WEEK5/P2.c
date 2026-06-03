#include <stdio.h>

#define N 5

void dining(int ph)
{
    printf("\nPhilosopher %d is Thinking", ph);

    printf("\nPhilosopher %d takes Fork %d and Fork %d",
           ph, ph, (ph + 1) % N);

    printf("\nPhilosopher %d is Eating", ph);

    printf("\nPhilosopher %d puts down Fork %d and Fork %d\n",
           ph, ph, (ph + 1) % N);
}

int main()
{
    int ph;

    printf("Enter Philosopher Number (0-4): ");
    scanf("%d", &ph);

    if(ph >= 0 && ph < N)
        dining(ph);
    else
        printf("Invalid Philosopher Number");

    return 0;
}
