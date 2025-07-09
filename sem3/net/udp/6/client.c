#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    char* IP = (char*)malloc(sizeof(argv[1]));
    strcpy(IP, argv[1]);
    const int PORT = atoi(argv[2]);

    int s = socket(AF_INET, SOCK_DGRAM, 0);
    if (s < 0) {
        perror("Cannot create socket");
        exit(0);
    }

    struct sockaddr_in server,client;
    memset(&server, 0, sizeof(server));
    server.sin_port = htons(PORT);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(IP);
    int length = sizeof(server);

    printf("Enter the number of characters: ");
    int n;
    scanf("%d", &n);
    printf("Enter the string: ");
    char* str = (char*)malloc((n + 1) * sizeof(char));
    scanf("%s", str);
    printf("Enter the character: ");
    char ch;
    scanf(" %c", &ch);
    sendto(s, &n, sizeof(n), 0, (struct sockaddr *)&server, sizeof(server));
    sendto(s, str, (n + 1) * sizeof(char), 0, (struct sockaddr *)&server, sizeof(server));
    sendto(s, &ch, sizeof(char), 0, (struct sockaddr *)&server, sizeof(server));

    int cnt;
    recvfrom(s, &cnt, sizeof(int), 0, (struct sockaddr *)&client, &length);
    int* ans = (int*)malloc(cnt * sizeof(int));
    recvfrom(s, ans, cnt * sizeof(int), 0, (struct sockaddr *)&client, &length);

    printf("The letter %c appears in %s a number of %d times: ", ch, str, cnt);
    for (int i = 0;i < cnt;++i)
        printf("%d ", ans[i]);
    printf("\n");
    close(s);

}


