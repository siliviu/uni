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

    printf("Enter the number of characters: ");
    int n;
    scanf("%d", &n);
    int nn = htonl(n);
    send(s, &nn, sizeof(nn), 0);
    getc(stdin);
    for (int i = 0;i < n;++i) {
        char x;
        scanf("%c", &x);
        int y;
        y = htonl(x);
        // printf("Sent %c\n", x);
        send(s, &y, sizeof(y), 0);
    }

    int cnt;
    recv(s, &cnt, sizeof(cnt), 0);
    cnt = ntohl(cnt);
    printf("The number of spaces is %d\n", cnt);

    close(s);
}


