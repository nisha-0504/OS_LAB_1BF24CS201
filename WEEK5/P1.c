#include <stdio.h>

int mutex = 1;
int full = 0;
int empty = 3, x = 0;

int wait(int s)
{
    return --s;
}

int signal(int s)
{
    return ++s;
}

int main()
{
    int n, ch;

    printf("Enter number of operations: ");
    scanf("%d", &n);

    for(int i = 0; i < n; i++)
    {
        printf("\n1. Produce\n2. Consume\nEnter choice: ");
        scanf("%d", &ch);

        switch(ch)
        {
            case 1:
                if(empty != 0)
                {
                    mutex = wait(mutex);
                    full = signal(full);
                    empty = wait(empty);
                    x++;
                    printf("Producer produces item %d\n", x);
                    mutex = signal(mutex);
                }
                else
                {
                    printf("Buffer is Full!\n");
                }
                break;

            case 2:
                if(full != 0)
                {
                    mutex = wait(mutex);
                    full = wait(full);
                    empty = signal(empty);
                    printf("Consumer consumes item %d\n", x);
                    x--;
                    mutex = signal(mutex);
                }
                else
                {
                    printf("Buffer is Empty!\n");
                }
                break;

            default:
                printf("Invalid Choice\n");
        }
    }

    return 0;
}
