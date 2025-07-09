#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include <stdlib.h>

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
    server.sin_addr.s_addr = inet_addr("172.18.208.10");

    if (bind(s, (struct sockaddr*)&server, sizeof(server)) < 0) {
        perror("Cannot create bind");
        exit(0);
    }

    listen(s, 5);

    struct sockaddr_in client;
    int length = sizeof(client);
    memset(&client, 0, sizeof(client));

    while (1) {
        int client = accept(s, (struct sockaddr*)&client, &length);
        printf("A client has connected.\n");

        int n = 2;
        // printf("Received %d\n", n);
        short sum = 0;
        for (int i = 0;i < n;++i) {
            short x;
            recv(client, &x, sizeof(x), MSG_WAITALL);
            x = ntohs(x);
            // printf("Received %d\n", numbers[i]);
            sum += x;
        }
        sum = htons(sum);
        send(client, &sum, sizeof(sum), 0);
        // printf("Done\n");

        close(client);
    }
}