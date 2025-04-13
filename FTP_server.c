#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#define PORT 6011
#define bs 1024

int main(){
	int server_sock, client_sock;
	struct sockaddr_in server_addr;
	char buffer[bs], command[20], fileName[20];
	int n;
	
	server_sock = socket(AF_INET, SOCK_STREAM, 0);
	
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(PORT);
	server_addr.sin_addr.s_addr = INADDR_ANY;
	
	bind(server_sock, (struct sockaddr*)&server_addr, sizeof(server_addr));
	
	listen(server_sock,5);
	
	client_sock = accept(server_sock,NULL,NULL);
	
	read(client_sock, command, sizeof(command));
	read(client_sock, fileName, sizeof(fileName));
	
	FILE *fp;
	if(strcmp(command,"put")==0){
		fp=fopen("newPutFile.txt","w");
		while((n=read(client_sock, buffer, sizeof(buffer)))>0){
			fwrite(buffer, sizeof(char), n, fp);
		}
		fclose(fp);
	}else if(strcmp(command,"get")==0){
		fp=fopen(fileName,"r");
		while((n=fread(buffer, sizeof(char), sizeof(buffer), fp))>0){
			write(client_sock, buffer, n);
		}
		fclose(fp);
	}
	
	close(client_sock);
	close(server_sock);
}
