#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 5

sem_t fork_sem[N];
sem_t mutex;

void *philosopher(void *arg)
{
    int id = *(int *)arg;

    while (1)
    {
        printf("Philosopher %d is Thinking\n", id);
        sleep(1);

        sem_wait(&mutex);

        sem_wait(&fork_sem[id]);           // Left Fork
        sem_wait(&fork_sem[(id + 1) % N]); // Right Fork

        printf("Philosopher %d is Eating\n", id);
        sleep(2);

        sem_post(&fork_sem[id]);
        sem_post(&fork_sem[(id + 1) % N]);

        sem_post(&mutex);
    }
}

int main()
{
    pthread_t p[N];
    int id[N];

    sem_init(&mutex, 0, 1);

    for (int i = 0; i < N; i++)
        sem_init(&fork_sem[i], 0, 1);

    for (int i = 0; i < N; i++)
    {
        id[i] = i;
        pthread_create(&p[i], NULL, philosopher, &id[i]);
    }

    for (int i = 0; i < N; i++)
        pthread_join(p[i], NULL);

    return 0;
}
