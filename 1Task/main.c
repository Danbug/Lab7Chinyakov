#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

const long WAIT_TIME = 2;
const int REPEAT_TIMES = 10;

// Thread Function
void * any_func(void * args) {
    for (int i = 0; i < REPEAT_TIMES; i++) {
        fprintf(stderr, "Child Thread. Iteration: %d\n", (i+1));
        sleep(WAIT_TIME);
    }
    return NULL;
}

// gcc main.c -o main -lpthread 
int main(void) {
    pthread_t thread;
    if (pthread_create(&thread, NULL, &any_func, NULL) != 0) {
        fprintf(stderr, "Error\n");
        return 1;
    }

    //pthread_join(thread,NULL);

    for (int i = 0; i < REPEAT_TIMES; i++) {
        fprintf(stderr, "Parent Thread. Iteration: %d\n", (i+1));
        sleep(WAIT_TIME);
    }

    return 0;
}