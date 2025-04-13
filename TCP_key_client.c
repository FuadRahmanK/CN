#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define port 7894
#define bs 1024

int main(){
	int sockfd, key;
	struct sockaddr_in server_addr, client_addr;
	char buffer[bs];
	
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(port);
	server_addr.sin_addr.s_addr = INADDR_ANY;
	
	bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
	
	connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
	
	printf("Enter key: ");
	scanf("%d",&key);
	write(sockfd, &key, sizeof(key));
	
	read(sockfd, buffer, bs);
	
	printf("Value of key is %s\n",buffer);
	
	close(sockfd);
	return 0;
}
