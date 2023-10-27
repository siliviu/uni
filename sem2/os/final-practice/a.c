#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

int main() {
    dup2(open("c.txt", O_WRONLY | O_CREAT), 1);
    execlp("cat","cat","a.txt", NULL);
}
