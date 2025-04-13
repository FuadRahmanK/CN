#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<arpa/inet.h>
#include<unistd.h>

#define port 9009

int main()
	{
	int sock=socket(AF_INET,SOCK_DGRAM,0);
	struct sockaddr_in server_addr, client_addr;
	socklen_t cli_len=sizeof(client_addr);
	int n1,n2,sum;
	
	memset(&server_addr,0,sizeof(server_addr));
	memset(&client_addr,0,sizeof(client_addr));
	
	server_addr.sin_family=AF_INET;
	server_addr.sin_port=htons(port);
	server_addr.sin_addr.s_addr=INADDR_ANY;
	
	bind(sock,(struct sockaddr*)&server_addr,sizeof(server_addr));
	
	recvfrom(sock, &n1, sizeof(n1),0,(struct sockaddr*)&client_addr, &cli_len);
	recvfrom(sock, &n2, sizeof(n2),0,(struct sockaddr*)&client_addr,&cli_len);
	
	sum=n1+n2;
	
	sendto(sock, &sum, sizeof(sum),0,(struct sockaddr*)&client_addr,cli_len);
	
	close(sock);
	return 0 ;
	}
	
