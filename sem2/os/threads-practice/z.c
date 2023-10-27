#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

void* test(void* arg) {
    printf("OHLALA");

}

int main() {
    int fd = open("random-file",O_RDONLY);
    for(int i=0;i<100;++i){
        unsigned x;
        read(fd,&x,sizeof(int));
        printf("%u ", x);
    }
    printf("\n");
    pthread_t p;
    pthread_create(&p,NULL, test, NULL);
    pthread_join(p, NULL);
    pthread_mutex_t mtx;
    pthread_mutex_init(&mtx, NULL);
    pthread_mutex_lock(&mtx);
    pthread_mutex_unlock(&mtx);
    pthread_mutex_destroy(&mtx);

    pthread_cond_t cond;
    pthread_cond_init(&cond, NULL);
    
    pthread_mutex_lock(&mtx);
    do{
    pthread_cond_wait(&cond, &mtx);
    } while(false);
    pthread_cond_broadcast(&cond);
    pthread_mutex_unlock(&mtx);

    pthread_cond_destroy(&cond);
 
    pthread_barrier_t bar;
    pthread_barrier_init(&bar, NULL, 1);
    pthread_barrier_wait(&bar);
    pthread_barrier_destroy(&bar);   

    pthread_rwlock_t lock;
    pthread_rwlock_init(&lock, NULL);
    pthread_rwlock_rdlock(&lock);
    pthread_rwlock_unlock(&lock);
    pthread_rwlock_wrlock(&lock);
    pthread_rwlock_unlock(&lock);
    pthread_rwlock_destroy(&lock);
}

