#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char** argv) {
    if (!freopen("file.txt","r",stdin)) {
        perror("open failed");
        exit(1);
    }
    int pd[2];
    if(pipe(pd) == -1) {
        perror("pipe");
        exit(1);    
    }
    int pid = fork();
    if(pid == -1) {
        perror("fork");
        exit(1);
    }
    if(pid == 0) {
        close(pd[1]); // close write 
        while(1) {
            char ch;
            read(pd[0], &ch, sizeof(char));
            printf("Received %c\n", ch);
            sleep(1);
            char s[50];
            read(pd[0], s, sizeof(s));
            printf("Received %s\n", s);
            if (strcmp(s, "stop") == 0)
                break;
         }
        close(pd[0]); // close read
        exit(0);
    }
    close(pd[0]); // close read
    while(1) {
        char ch;
//        printf("Enter a character:\n");
        scanf("%c", &ch);
        getchar();
        write(pd[1], &ch, sizeof(ch));
        sleep(1);
        char s[50];
//        printf("Enter an array:\n");
        scanf("%s", s);
        getchar();
        write(pd[1], s, sizeof(s));
        if (strcmp(s, "stop") == 0)
              break;
    }
    close(pd[1]);
    wait(0);      
}
