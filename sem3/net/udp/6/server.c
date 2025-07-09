#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    const int PORT = atoi(argv[1]);

    int s = socket(AF_INET, SOCK_DGRAM, 0);
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

    struct sockaddr_in client;
    int length = sizeof(client);

    while (1) {
        printf("Waiting\n");
        int n;
        recvfrom(s, &n, sizeof(n), 0, (struct sockaddr *)&client, &length);
        char* str = (char*)malloc((n + 1) * sizeof(char));
        recvfrom(s, str, (n + 1) * sizeof(char), 0, (struct sockaddr *)&client, &length);
        char ch;
        recvfrom(s, &ch, sizeof(char), 0, (struct sockaddr *)&client, &length);

        int cnt = 0;
        int* ans = (int*)malloc(n * sizeof(int));
        for (int i = 0;i < n;++i)
            if (str[i] == ch)
                ans[cnt++] = i;
        sendto(s, &cnt, sizeof(int), 0, (struct sockaddr *)&client, length);
        sendto(s, ans, cnt * sizeof(int), 0, (struct sockaddr *)&client, length);
        printf("Handled client\n");
    }
    close(s);
}