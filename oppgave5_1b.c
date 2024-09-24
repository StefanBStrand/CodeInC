#include <pthread.h>
#include <stdio.h>

#define N_THREADS 5

int value = 0;  // Global variable shared by all threads
pthread_mutex_t lock;  // Declare a mutex lock

void *count()
{
    int i;

    pthread_mutex_lock(&lock);  // Lock the mutex before accessing shared data

    for (i = 0; i < 100000; i++)
        value++;  // Increment the global variable

    printf("%d ", value);  // Print the current value

    pthread_mutex_unlock(&lock);  // Unlock the mutex after accessing shared data
}

int main ()
{
    int i;
    pthread_t thread[N_THREADS];

    pthread_mutex_init(&lock, NULL);  // Initialize the mutex

    for(i = 0; i < N_THREADS; i++)
        pthread_create(&thread[i], NULL, count, NULL);  // Create threads

    for(i = 0; i < N_THREADS; i++)
        pthread_join(thread[i], NULL);  // Wait for each thread to finish

    pthread_mutex_destroy(&lock);  // Destroy the mutex after all threads are done

    printf("\n");
}
