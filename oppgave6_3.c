#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define MAX_WAIT 2000000

pthread_mutex_t mutex;
pthread_cond_t cond;
int blocked_threads = 0;

void *terningkast(void *nr)
{
    while(1)
    {
        int terning = rand() % 6 + 1;

        pthread_mutex_lock(&mutex);
        if (terning == 1) {
            blocked_threads++;
            printf("Tråd %3ld -> %d (%d)\n", (long) nr, terning, blocked_threads);
            pthread_cond_wait(&cond, &mutex);
            blocked_threads--;
        }
        else if (terning == 6) {
            pthread_cond_signal(&cond);
            printf("Tråd %3ld -> %d (%d)\n", (long) nr, terning, blocked_threads);
        }
        else {
            printf("Tråd %3ld -> %d\n", (long) nr, terning);
        }

        pthread_mutex_unlock(&mutex);

        usleep(rand() % MAX_WAIT + 1);
    }
}

int main()
{
    int n;
    long i;
    pthread_t t;

    printf("n? ");
    scanf("%d", &n);

    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond, NULL);

    for (i = 0; i < n; i++)
        pthread_create(&t, NULL, terningkast, (void *) i);

    pthread_join(t, NULL);

}
