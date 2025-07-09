#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <assert.h>

#define MAX_THR 100
#define MAX_NUM 10'000'000
#define MAX_VAL 100
#define CHUNK MAX_NUM/MAX_THR

int numbers[MAX_NUM];

int ans = 0, ans2 = 0;

pthread_mutex_t mx;

void* do_sum(void* a){
    int v=*(int*)(a);
    free(a);
    int sum = 0;
    for(int i=v*CHUNK;i<(v+1)*CHUNK;++i)
        sum+=numbers[i];
    pthread_mutex_lock(&mx);
    ans+=sum;   
    pthread_mutex_unlock(&mx);
    return NULL;
}

int main(int argc, char** argv){
    srand(time(NULL));
    pthread_mutex_init(&mx, NULL);
    for(int i=0;i<MAX_NUM;++i){
        numbers[i]=rand()%MAX_VAL;
        ans2+=numbers[i];
    }
    pthread_t tid[MAX_THR];
    for(int i=0;i<MAX_THR;++i){
        int* arg = (int*)malloc(sizeof(int));
        *arg=i;
        pthread_create(&tid[i],NULL,do_sum,arg);
    }
    for(int i=0;i<MAX_THR;++i)
        pthread_join(tid[i], NULL);
    assert(ans==ans2);
    printf("The sum is: %d\n",ans);
}
