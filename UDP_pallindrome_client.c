#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 8095
#define bs 1024

int main() {
    int sockfd;
    struct sockaddr_in server_addr;
    int len = sizeof(server_addr);
    char buffer[bs];
    char res[bs];

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    printf("Enter a string: ");
    scanf("%s",buffer);

    sendto(sockfd, buffer, bs, 0, (struct sockaddr*)&server_addr, sizeof(server_addr));
    
    recvfrom(sockfd, res, bs, 0, (struct sockaddr*)&server_addr, &len);
    
    printf("%s\n", res);

    close(sockfd);
    return 0;
}

