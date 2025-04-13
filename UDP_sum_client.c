#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>

#define port 9009

int main()
	{
	int sock=socket(AF_INET,SOCK_DGRAM,0);
	struct sockaddr_in server_addr;
	int n1,n2,s;
	
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(port);
	server_addr.sin_addr.s_addr = INADDR_ANY;
    
	printf("Enter number 1: ");
	scanf("%d",&n1);
	printf("Enter number 2:");
	scanf("%d",&n2);
	
	sendto(sock,&n1,sizeof(n1),0,(struct sockaddr*)&server_addr,sizeof(server_addr));
	sendto(sock,&n2,sizeof(n2),0,(struct sockaddr*)&server_addr,sizeof(server_addr));
	
	int len=sizeof(server_addr);
	recvfrom(sock,&s,sizeof(s),0,(struct sockaddr*)&server_addr,&len);
	
	printf("The sum of the numbers recieved from the server is :%d\n",s);
	
	close(sock);
	return 0;
	}
	
