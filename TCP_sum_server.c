#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8090

int main(){
	int server_sock, client_sock, num1, num2, sum;
	struct sockaddr_in server_addr, client_addr;
	socklen_t client_len = sizeof(client_addr);
	
	server_sock = socket(AF_INET, SOCK_STREAM, 0);
	
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = INADDR_ANY;
	server_addr.sin_port=htons(PORT);
	
	bind(server_sock, (struct sockaddr*)&server_addr, sizeof(server_addr));
	
	listen(server_sock, 5);
	while(1){
		client_sock = accept(server_sock, (struct sockaddr*)&client_addr, &client_len);
	
		while(1){
			read(client_sock, &num1, sizeof(num1));
			read(client_sock, &num2, sizeof(num2));
	
			sum= num1+num2;
	
			write(client_sock, &sum, sizeof(sum));
		}
		close(client_sock);
	}
	close(server_sock);
	return 0;
}
	
	
