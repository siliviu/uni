#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <fcntl.h>

const int PRODUCER_WORK = 1 << 14, BUFFER_SIZE = 1 << 12;

pthread_barrier_t barrier;
int N, M;

typedef struct { 
    pthread_mutex_t mtx;
    pthread_cond_t cond;
    int nr, pos = 0, buf[BUFFER_SIZE];
    int sum = 0;
} data;

void* consume(void* arg) {
    data* buffer = (data*)(arg);
    printf("Created consumer \n");
    int work = (N * PRODUCER_WORK) / (BUFFER_SIZE * M);
    while (work--) {
        pthread_mutex_lock(&buffer->mtx);
        while (buffer->pos != BUFFER_SIZE)
            pthread_cond_wait(&buffer->cond, &buffer->mtx);
        for (int i = 0; i < BUFFER_SIZE; ++i)
            buffer->sum += buffer->buf[i];
        printf("Consumed %d. Sum = %d\n", buffer->nr, buffer->sum);
        buffer->pos = 0;
        pthread_cond_broadcast(&buffer->cond);    
        pthread_mutex_unlock(&buffer->mtx);
    }
    printf("Returned consumer %d with sum %d\n", buffer->nr, buffer->sum);
    pthread_barrier_wait(&barrier);
    printf("ALL DONE\n");
    return NULL;
}

void* produce(void* arg) {
    int work = PRODUCER_WORK;
    data* buffer = (data*)(arg);
    printf("Created producer\n");
    while (work--) {
        pthread_mutex_lock(&buffer->mtx);
        while (buffer->pos == BUFFER_SIZE)
            pthread_cond_wait(&buffer->cond, &buffer->mtx);
        buffer->buf[(buffer->pos)++] = rand() % 16;
        if (buffer->pos == BUFFER_SIZE)
            pthread_cond_broadcast(&buffer->cond);
        pthread_mutex_unlock(&buffer->mtx);
    }
    printf("Returned producer\n");
    return NULL;
}

int main(int argc, char** argv) {
    if (argc != 3) {
        printf("Usage : %s NR_PROD NR_CONS\n", argv[0]);
        exit(0);
    }
    N = atoi(argv[1]), M = atoi(argv[2]);
    data* buffer = (data*)malloc(M*sizeof(data));
    pthread_t* cons = (pthread_t*)malloc(M*sizeof(pthread_t));
    pthread_barrier_init(&barrier, NULL, M);
    for (int i = 0; i < M; ++i) {
        pthread_mutex_init(&buffer[i].mtx, NULL);
        pthread_cond_init(&buffer[i].cond, NULL);
        pthread_create(&cons[i], NULL, consume, &buffer[i]);
        buffer[i].nr = i;
    }
    pthread_t* prod = (pthread_t*)malloc(N*sizeof(pthread_t));
    for (int i = 0; i < N; ++i)
        pthread_create(&prod[i], NULL, produce, &buffer[i % M]);
    for (int i = 0; i < M; ++i)
        pthread_join(cons[i], NULL);
    for (int i = 0; i < N; ++i)
        pthread_join(prod[i], NULL);
    int sum = 0;
    for (int i = 0; i < M; ++i) {
        pthread_cond_destroy(&buffer[i].cond);
        pthread_mutex_destroy(&buffer[i].mtx);
        sum += buffer[i].sum;
    }
    printf("Total sum: %d\n", sum);
    free(buffer), free(cons), free(prod);
    pthread_barrier_destroy(&barrier);
}
