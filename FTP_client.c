#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 6011
#define bs 1024

int main(){
	int sock_fd;
	struct sockaddr_in server_addr;
	char command[20], fileName[20], buffer[bs];
	int n;
	
	sock_fd = socket(AF_INET, SOCK_STREAM, 0);
	
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(PORT);
	server_addr.sin_addr.s_addr = INADDR_ANY;
	
	bind(sock_fd, (struct sockaddr*)&server_addr, sizeof(server_addr));
	
	connect(sock_fd, (struct sockaddr*)&server_addr, sizeof(server_addr));
	
	printf("Enter command: ");
	scanf("%s",command);
	printf("Enter filename: ");
	scanf("%s",fileName);
	write(sock_fd, command, sizeof(command));
	write(sock_fd, fileName, sizeof(fileName));
	
	FILE *fp;
	if(strcmp(command,"put")==0){
		fp=fopen(fileName, "r");
		while((n=fread(buffer, sizeof(char), sizeof(buffer), fp))>0){
			write(sock_fd, buffer, n);
		}
		fclose(fp);
	}else if(strcmp(command,"get")==0){
		fp=fopen("newGetFile.txt","w");
		while((n=read(sock_fd, buffer, sizeof(buffer)))>0){
			fwrite(buffer, sizeof(char), n, fp);
		}
		fclose(fp);
	}
	
	close(sock_fd);
}
