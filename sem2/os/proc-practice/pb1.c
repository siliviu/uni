#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <time.h>
#include <assert.h>

enum PIPE { AB, BA };
enum MODE { R, W };

int pd[2][2];

void B() {
    // B
    close(pd[AB][W]), close(pd[BA][R]);
    int left = 1000, right = 10000, m;
    char r;
    while (left < right) {
        m = (left + right) / 2;
        write(pd[BA][W], &m, sizeof(int));
        printf("Sent to A: %d\n", m);
        read(pd[AB][R], &r, sizeof(char));
        printf("Received from A: %c\n", r);
        if (r == '<')
            left = m + 1;
        else if (r == '>')
            right = m;
        else {
            left = m;
            break;
        }
    }
    printf("B: X is %d\n", left);
    exit(0);
}

void A() {
    // A
    close(pd[AB][R]), close(pd[BA][W]);
    srand(time(0));
    int x = 1000 + (rand() % 9001);
    //int x = 9999;
    printf("A: X is %d\n", x);
    char c;
    int v;
    while (1) {
        read(pd[BA][R], &v, sizeof(int));
        printf("Read from B: %d\n", v);
        c = v < x ? '<' : v == x ? '=' : '>';
        write(pd[AB][W], &c, sizeof(char));
        printf("Sent to B: %c\n", c);
        if (c == '=')
            break;
    }
    wait(0);
}

int main(int argc, char** argv) {
    if (pipe(pd[AB]) < 0 || pipe(pd[BA]) < 0) {
        perror("pipe");
        error(0);
    }

    int v = fork();
    if (v < 0) {
        perror("fork");
        exit(0);
    }
    if (v == 0)
        B();
    else
        A();
}
