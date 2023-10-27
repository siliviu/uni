#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

const int NR = 10;
pthread_mutex_t a, b;
int n;

void*fa(void*aa){
    int t=1;
    while(t--){
    pthread_mutex_lock(&a);
    ++n;
    pthread_mutex_unlock(&a);
    }
    return NULL;
}

void*fb(void*aa){
    int t=1;
    while(t--){
    pthread_mutex_lock(&b);
    ++n;
    pthread_mutex_unlock(&b);
    }
    return NULL;
}

int main() {
    pthread_mutex_init(&a, NULL);
    pthread_mutex_init(&b, NULL);
    pthread_t t[NR];
    for (int i = 0 ;i < NR; ++i)
        pthread_create(&t[i], NULL, i%2 ? fa:fb,NULL);
    for(int i=0;i<NR;++i)
        pthread_join(t[i],NULL);
    pthread_mutex_destroy(&a);
    pthread_mutex_destroy(&b);
    printf("%d",n);
}
