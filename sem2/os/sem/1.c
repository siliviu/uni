#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define MAX_THR 100

void* f(void* a) {
    //int id = (long long)a;
    int id = *(int*)a;
    free(a);
    printf("Thread: %d\n", id);
    return 0;
}

int main(int argc, char** argv) {
    pthread_t tid[MAX_THR];
    for(int i = 0; i < MAX_THR; ++i){
        //pthread_create(&tid[i], NULL, f, (void*)i);    
        int *p = (int*)malloc(sizeof(int));
        *p = i;
        pthread_create(&tid[i], NULL, f, p);    
    }
    for(int i = 0; i < MAX_THR; ++i)
        pthread_join(tid[i], 0);
}
