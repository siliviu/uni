#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>


// reader
int main(int argc, char** argv) {
    int pd = open("fifo1",O_RDONLY);
    if (pd == -1) {
        perror("open");
        exit(1);
    }
    while(1) {
            char ch;
            read(pd, &ch, sizeof(char));
            printf("Received %c\n", ch);
            sleep(1);
            char s[50];
            read(pd, s, sizeof(s));
            printf("Received %s\n", s);
            if (strcmp(s, "stop") == 0)
                break;
    }
    close(pd);
}

