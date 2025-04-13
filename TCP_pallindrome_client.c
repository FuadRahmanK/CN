#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<arpa/inet.h>
#include<unistd.h>

#define port 8809
#define bs 1024

int main()
	{
	int client_sock;
	struct sockaddr_in server_addr;
	char buffer[bs];
	char res[bs];
	
	client_sock=socket(AF_INET,SOCK_STREAM,0);
	server_addr.sin_family=AF_INET;
	server_addr.sin_port=htons(port);
	server_addr.sin_addr.s_addr=INADDR_ANY;
	
	connect(client_sock, (struct sockaddr*)&server_addr, sizeof(server_addr));
	
	printf("Enter a string to check palindrom or not: ");
	scanf("%s",buffer);
	
	write(client_sock, buffer,bs);
	
	read(client_sock,res,bs);
	printf("result from server: %s", res);
	
	close(client_sock);
	return 0;
	}

