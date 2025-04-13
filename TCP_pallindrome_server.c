#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<arpa/inet.h>
#include<unistd.h>

#define port 8809
#define bs 1024

int main()
	{
	int server_sock,client_sock;
	char buffer[bs];
	
	struct sockaddr_in server_addr,client_addr;
	socklen_t client_len= sizeof(client_addr);

	server_sock=socket(AF_INET,SOCK_STREAM,0);
	
	server_addr.sin_family=AF_INET;
	server_addr.sin_port= htons(port);
	server_addr.sin_addr.s_addr=INADDR_ANY;
	
	bind(server_sock, (struct sockaddr*)&server_addr,sizeof(server_addr));
	
	listen(server_sock,5);
	
	client_sock = accept(server_sock,(struct sockaddr*)&client_addr,&client_len);

	read(client_sock,buffer,bs);
	
	printf("Recieved string is :%s\n", buffer);
	
	int f=0;
	int len=strlen(buffer);
	for (int i=0;i<len/2;i++){
		if (buffer[i] != buffer[len-i-1]){ 
			f=1;
		}
	}
	if(f==0){ 
		strcpy(buffer,"is palindrome");
	}else{ 
		strcpy(buffer,"is not palindrome");
	}
	write(client_sock, buffer,bs);
	
	close(client_sock);
	
	close(server_sock);
	return 0;
	}
	
	
	
	
	
	
	
	
	
