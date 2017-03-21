#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

// Create two mutex locks
pthread_mutex_t resource1;
pthread_mutex_t resource2;

// The functions used for the seperate threads

// This function is for thread 1
void *threadOne(void *args)
{
    pthread_mutex_lock(&resource1);
    pthread_mutex_lock(&resource2);
    printf("Thread 1 has both resources, and is running!\n");
    pthread_mutex_unlock(&resource2);
    pthread_mutex_unlock(&resource1);
    printf("Thread 1 is done!\n");
    pthread_exit(0);
    return NULL;
}

// This function is for thread 2
void *threadTwo(void *args)
{
    pthread_mutex_lock(&resource2);
    pthread_mutex_lock(&resource1);
    printf("Thread 2 has both resources, and is running!\n");
    pthread_mutex_unlock(&resource1);
    pthread_mutex_unlock(&resource2);
    printf("Thread 2 is done!\n");
    pthread_exit(0);
    return NULL;
}

int main()
{
    int n = 0;

    // Create the ids for each of the threads
    pthread_t tidOne;
    pthread_t tidTwo;


    // Run a loop to try to get a deadlock
    while (n < 1000)
    {
        pthread_create(&tidOne, NULL, &threadOne, NULL);
        pthread_create(&tidTwo, NULL, &threadTwo, NULL);

        n++;
    }

    pthread_join(tidOne, NULL);
    pthread_join(tidTwo, NULL);
}
