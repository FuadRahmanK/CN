#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 8095
#define bs 1024

int main() {
    int sockfd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);
    char buffer[bs];

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    
    recvfrom(sockfd, buffer, bs, 0, (struct sockaddr*)&client_addr, &client_len);

    int f=0;
    int len=strlen(buffer);
    for(int i=0; i<len/2; i++){
    	if(buffer[i] != buffer[len-i-1]){
    		f=1;
    	}
    }
    if(f==0){
    	strcpy(buffer,"is pallindrome");
    }else{
    	strcpy(buffer,"is not pallindrome");
    }
    
    sendto(sockfd, buffer, bs, 0, (struct sockaddr*)&client_addr, client_len);

    close(sockfd);
    return 0;
}

