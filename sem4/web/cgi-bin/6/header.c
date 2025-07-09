#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[], char *envp[]){
    printf("Content-type: text/html\n");
    printf("\n");
    printf("Headers: \n");
    for (int i = 0; envp[i]; i++)
        printf("%s\n", envp[i]);
}