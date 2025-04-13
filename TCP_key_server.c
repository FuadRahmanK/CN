#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define port 7894
#define bs 1024

struct table{
	int key;
	char value[100];
}a[5];

int main(){
	a[0].key=100;
	strcpy(a[0].value,"Apple");
	a[1].key=101;
	strcpy(a[1].value,"Banana");
	a[2].key=102;
	strcpy(a[2].value,"Orange");
	a[3].key=103;
	strcpy(a[3].value,"Grape");
	a[4].key=104;
	strcpy(a[4].value,"Mango");
	
	int server_sock, client_sock, key;
	struct sockaddr_in server_addr, client_addr;
	socklen_t client_len = sizeof(client_addr);
	char buffer[bs];
	
	server_sock = socket(AF_INET, SOCK_STREAM, 0);
	
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(port);
	server_addr.sin_addr.s_addr = INADDR_ANY;
	
	bind(server_sock, (struct sockaddr*)&server_addr, sizeof(server_addr));
	
	listen(server_sock, 5);
	
	client_sock = accept(server_sock, (struct sockaddr*)&client_addr, &client_len);
	
	read(client_sock, &key, sizeof(key));
	
	for(int i=0; i<5; i++){
		if(a[i].key==key){
			strcpy(buffer,a[i].value);
			break;
		}else{
			strcpy(buffer,"Key not found");
		}
	}
	write(client_sock, buffer, bs);
		
	close(client_sock);
	close(server_sock);
	return 0;
}
