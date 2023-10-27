#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>


// writer
int main(int argc, char** argv) {
    int pd = open("fifo1",O_WRONLY);
    if (pd == -1) {
        perror("open");
        exit(1);
    }
    while (1) {
         char ch;
         printf("Enter a character:\n");
         scanf("%c", &ch);
         getchar();
         write(pd, &ch, sizeof(ch));
         sleep(1);
         char s[50];
         printf("Enter an array:\n");
         scanf("%s", s);
         getchar();
         write(pd, s, sizeof(s));
         if (strcmp(s, "stop") == 0)
               break;        
    }
    close(pd);
}

