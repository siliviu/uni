#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

void handle_client(int client) {
    // wait for request (3 letter string + '\0')
    char buffer[512];
    ssize_t recv_result = recv(client, &buffer, 4 * sizeof(char), MSG_WAITALL);
    buffer[recv_result] = '\0';
    printf("Received %s\n", buffer);

    //handle request
    if (strcmp(buffer, "ORA") == 0) {
        // get unix time in minutes
        int passed = time(NULL) / 60;

        // convert to string
        char str[32] = {};
        sprintf(str, "%d", passed);

        // send to client
        send(client, &str, 31, 0);
        printf("Sent %d\n", passed);
    }

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
        printf("A client has connected with ip %s.\n", inet_ntoa(client.sin_addr));
        if (fork() == 0)
            handle_client(c);
    }
}