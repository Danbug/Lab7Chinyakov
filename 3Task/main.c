#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

const long WAIT_TIME = 2;

// Thread Function
void *any_func(void *args)
{
    int repetitions = *(int *)args;
    for (int i = 0; i < repetitions; i++)
    {
        fprintf(stderr, "Child Thread. Iteration: %d\n", (i + 1));
        //sleep(WAIT_TIME);
    }
    return NULL;
}

void *second_func(void *arg)
{
    srand(time(NULL));
    int toGenerate = *(int *)arg;

    int rng = 0;
    do
    {
        rng = rand() % 10;
        printf("RNG Thread generated = %d\n", rng);
    } while (rng != toGenerate);

    printf("RNG = %d, TO GENERATE = %d, I'M OUT\n\n\n", rng, toGenerate);

    return NULL;
}

// gcc main.c -o main -lpthread
int main(void)
{
    int toGenerate = 5;
    int repeatTimes = 5;
    pthread_t thread, thread2;

    if (pthread_create(&thread, NULL, &any_func, &repeatTimes) != 0)
    {
        fprintf(stderr, "Error\n");
        return 1;
    }

    if (pthread_create(&thread2, NULL, &second_func, &toGenerate) != 0)
    {
        fprintf(stderr, "Error\n");
        return 1;
    }

    pthread_join(thread, NULL);
    pthread_join(thread2, NULL);

    printf("\n\nPARENT end\n\n");

    return 0;
}