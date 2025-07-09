#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>

int main(int argc, char* argv[]) {
    char* IP = (char*)malloc(sizeof(argv[1]));
    strcpy(IP, argv[1]);
    const int PORT = atoi(argv[2]);

    int s = socket(AF_INET, SOCK_STREAM, 0);
    if (s < 0) {
        perror("Cannot create socket");
        exit(0);
    }

    struct sockaddr_in server;
    memset(&server, 0, sizeof(server));
    server.sin_port = htons(PORT);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(IP);

    if (connect(s, (struct sockaddr*)&server, sizeof(server)) < 0) {
        perror("Cannot connect to server");
        return 1;
    }

    printf("Enter the number of numbers: ");
    int n;
    scanf("%d", &n);
    int nn = htonl(n);
    send(s, &nn, sizeof(nn), 0);
    printf("Enter the numbers:\n");
    for (int i = 0;i < n;++i) {
        int x;
        scanf("%d", &x);
        x = htonl(x);
        // printf("Sent %d\n", x);
        send(s, &x, sizeof(x), 0);
    }

    int sum;
    recv(s, &sum, sizeof(sum), 0);
    sum = ntohl(sum);
    printf("The sum is %d\n", sum);

    close(s);
}


