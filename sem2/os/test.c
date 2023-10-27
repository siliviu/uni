#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>

const int S = 10000000, NR = 20;
sem_t sem;

int cnt = 0;

void* go (void* arg) {
    for(int i = 0; i < S / NR; ++i) {
        sem_wait(&sem);
        ++cnt;
        sem_post(&sem);
    }
}

int main () {
    sem_init(&sem, 0, 1);
    pthread_t a[NR];
    for (int i = 0; i < NR ; ++i)
        pthread_create(&a[i], NULL, go, NULL);
    for (int i = 0; i < NR ; ++i)
        pthread_join(a[i], NULL); 
    printf("%d", cnt);
}
