#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include <stdlib.h>

void handle_client(int client) {
    int n;
    recv(client, &n, sizeof(n), MSG_WAITALL);
    n = ntohl(n);
    // printf("Received %d\n", n);
    int cnt = 0;
    for (int i = 0;i < n;++i) {
        int x;
        recv(client, &x, sizeof(x), MSG_WAITALL);
        char y = ntohl(x);
        // printf("Received %c\n", y);
        cnt += y == ' ';
    }
    cnt = htonl(cnt);
    send(client, &cnt, sizeof(cnt), 0);
    // printf("Done\n");

    close(client);
    exit(0);
}

int main(int argc, char* argv[]) {
    const int PORT = atoi(argv[1]);

    int s = socket(AF_INET, SOCK_STREAM, 0);
    if (s < 0) {
        perror("Cannot create socket");
        exit(0);
    }

    struct sockaddr_in server;
    memset(&server, 0, sizeof(server));
    server.sin_port = htons(PORT);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;

    if (bind(s, (struct sockaddr*)&server, sizeof(server)) < 0) {
        perror("Cannot create bind");
        exit(0);
    }

    listen(s, 5);

    struct sockaddr_in client;
    int length = sizeof(client);
    memset(&client, 0, sizeof(client));

    while (1) {
        int c = accept(s, (struct sockaddr*)&client, &length);
        printf("A client has connected.\n");

        if (fork() == 0)
            handle_client(c);
    }
}