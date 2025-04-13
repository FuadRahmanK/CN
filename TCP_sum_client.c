#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8090

int main(){
	int server_sock, num1, num2, sum;
	struct sockaddr_in server_addr;
	int n;
	
	server_sock = socket(AF_INET, SOCK_STREAM, 0);
	
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = INADDR_ANY;
	server_addr.sin_port=htons(PORT);
	
	connect(server_sock, (struct sockaddr*)&server_addr, sizeof(server_addr));
	
	while(1){
		printf("Enter 1 to add or 0 to exit: ");
		scanf("%d",&n);
		if(n==1){
			printf("Enter num1: ");
			scanf("%d",&num1);
			printf("Enter num2: ");
			scanf("%d",&num2);
			write(server_sock, &num1, sizeof(num1));
			write(server_sock, &num2, sizeof(num2));
	
			read(server_sock, &sum, sizeof(sum));
	
			printf("Sum is %d\n",sum);
		}else if(n==0){
			break;
		}
	}
	close(server_sock);
	return 0;
}
