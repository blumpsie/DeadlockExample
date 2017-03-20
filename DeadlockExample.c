#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

// Struct for the multiple arguments
struct argStruct
{
   int arg1;
   int arg2;
};

// The functions used for the seperate threads
void *threadOne(void *arguments)
{
    struct argStruct *args = arguments;
    int num1 = args -> arg1;
    int num2 = args -> arg2;
    printf("Thread 1 has both resources, and is running!\n");
    int sum = num1 + num2;
    int sum2 = (args -> arg1) + (args -> arg2);
    pthread_exit(0);
    return NULL;
}

void *threadTwo(void *arguments)
{
    struct argStruct *args = arguments;
    int num2 = args -> arg2;
    int num1 = args -> arg1;
    printf("Thread 2 has both resources, and is running!\n");
    int product = num2 * num1;
    int product2 = (args -> arg2) + (args -> arg1);

    pthread_exit(0);
    return NULL;
}

int main()
{
    int n = 0;
    struct argStruct args;
    args.arg1 = 3;
    args.arg2 = 4;

    // Create the ids for each of the threads
    pthread_t tidOne;
    pthread_t tidTwo;


    // Run a loop to try to get a deadlock
    while (n < 1000)
    {
        int thread1 =  pthread_create(&tidOne, NULL, &threadOne, (void *)&args);
        int thread2 = pthread_create(&tidTwo, NULL, &threadTwo, (void *)&args);

        if(thread1)
        {
            printf("Thread 1 is done!\n");
        }

        if(thread2)
        {
            printf("Thread 2 is done!\n");
        }
        n++;
    }
}
