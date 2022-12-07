#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

void *katalan(void *args)
{
   int n = *(int *)args;
   int *arr = malloc(n * sizeof(int));

   // Initialize first two values in table
   arr[0] = arr[1] = 1;

   // Fill entries in arr[] using recursive formula
   for (int i = 2; i <= n; i++)
   {
      arr[i] = 0;
      for (int j = 0; j < i; j++)
         arr[i] += arr[j] * arr[i - j - 1];
   }
   pthread_exit(arr);
}

void *fibo(void *args)
{
   int n = *(int *)args;
   int *arr = malloc(n * sizeof(int));
   int counter = 0;
   do
   {
      // initialize first and second terms
      int t1 = 0, t2 = 1;
      arr[counter] = 0;
      counter++;
      arr[counter] = 1;
      counter++;

      // initialize the next term (3rd term)
      int nextTerm = t1 + t2;


      // print 3rd to nth terms
      for (int i = 3; i <= n; ++i)
      {
         arr[counter] = nextTerm;
         counter++;
         t1 = t2;
         t2 = nextTerm;
         nextTerm = t1 + t2;
      }
   } while (counter < n);

   pthread_exit(arr);
}

// gcc main.c -o main -lpthread
int main()
{
   pthread_t tid;
   pthread_t tid2;
   int size_katalan = 10;
   int size_fibo = 5;
   void *katalan_arr;
   void *fibo_arr;

   pthread_create(&tid, NULL, &katalan, &size_katalan);
   pthread_create(&tid2, NULL, &fibo, &size_fibo);
   pthread_join(tid, &katalan_arr);
   pthread_join(tid2, &fibo_arr);

   printf("Katalana nums\n");
   for (int i = 0; i < size_katalan; i++)
   {
      printf("%d ", ((int *)katalan_arr)[i]);
   }
   printf("\n");

   printf("fibo nums\n");
   for (int i = 0; i < size_fibo; i++)
   {
      printf("%d ", ((int *)fibo_arr)[i]);
   }
   printf("\n");

   free(katalan_arr);
   free(fibo_arr);

   return 0;
}