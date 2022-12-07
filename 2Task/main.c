#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

long WAIT_FOR_SECONDS = 3;

typedef struct toThread {
    char* name;
    char* baseStr;
    int num;
}ThreadData;

void * func_for_threads(void *args) {
    ThreadData my_structure = * (ThreadData* ) args;

    for (int i = 0; i < my_structure.num; ++i) {
        printf("Thread %s. Str %d/%d. Message: %s\n", my_structure.name, (i+1), my_structure.num, my_structure.baseStr);
    }
}


void check_if_error(int result) {
    if (result != 0) {
        fprintf(stderr, "Error during thread creation\n");
        exit(1);
    }
}

// gcc main.c -o main -lpthread
int main(void) {

    // ініціалізація структур
    ThreadData potik1, potik2, potik3, potik4;

    potik1.name = "Th 1";
    potik1.baseStr = "Hello";
    potik1.num = 7;

    potik2.name = "Th 2";
    potik2.baseStr = "World";
    potik2.num = 4;

    potik3.name = "Th 3";
    potik3.baseStr = "Lorem";
    potik3.num = 2;

    potik4.name = "Th 4";
    potik4.baseStr = "Ipsum";
    potik4.num = 5;

    // створення потоків
    pthread_t thread1, thread2, thread3, thread4;
    check_if_error(pthread_create(&thread1, NULL, &func_for_threads, &potik1));
    check_if_error(pthread_create(&thread2, NULL, &func_for_threads, &potik2));
    check_if_error(pthread_create(&thread3, NULL, &func_for_threads, &potik3));
    check_if_error(pthread_create(&thread4, NULL, &func_for_threads, &potik4));
    // pthread_join(thread1,NULL);
    // pthread_join(thread2,NULL);
    // pthread_join(thread3,NULL);
    // pthread_join(thread4,NULL);
    sleep(WAIT_FOR_SECONDS);

    return 0;
}