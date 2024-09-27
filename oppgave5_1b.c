#include <pthread.h>
#include <stdio.h>

#define N_THREADS 5

int value = 0;
pthread_mutex_t lock;

void *count()
{
    int i;

    pthread_mutex_lock(&lock);

    for (i = 0; i < 100000; i++)
        value++;

    printf("%d ", value);

    pthread_mutex_unlock(&lock);
}

int main ()
{
    int i;
    pthread_t thread[N_THREADS];

    pthread_mutex_init(&lock, NULL);

    for(i = 0; i < N_THREADS; i++)
        pthread_create(&thread[i], NULL, count, NULL);

    for(i = 0; i < N_THREADS; i++)
        pthread_join(thread[i], NULL);

    pthread_mutex_destroy(&lock);

    printf("\n");
}


// value -- > Global variable shared by all threads

// Declare a mutex lock
// Lock the mutex before accessing shared data (value)
// Unlock the mutex after accessing shared data
// Initialize the mutex