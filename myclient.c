#include <arpa/inet.h>
#include <netdb.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/types.h> 
#define MAX 80 
#define PORT 8080 
#define SA struct sockaddr 
void func(int sockfd1) 
{ 
    char buff[MAX]; 
    int n; 
    for (;;) { 
        bzero(buff, sizeof(buff)); 
        printf("Enter the string : "); 
        n = 0; 
        while ((buff[n++] = getchar()) != '\n') 
            ; 
        write(sockfd1, buff, sizeof(buff)); 
        bzero(buff, sizeof(buff)); 
        read(sockfd1, buff, sizeof(buff)); 
        printf("From Server : %s", buff); 
        if ((strncmp(buff, "exit", 4)) == 0) { 
            printf("Client Exit...\n"); 
            break; 
        } 
    } 
} 
  
int main() 
{ 
    int sockfd1, connfd; 
    struct sockaddr_in cliaddr1; 
    //socklen_t len;
    // socket create and varification 
    sockfd1 = socket(AF_INET, SOCK_STREAM, 0); 
    if (sockfd1 == -1) { 
        printf("socket creation failed...\n"); 
        exit(0); 
    } 
    else
    {
        printf("Socket successfully created..\n"); 
        printf("sockfd=%d\n",sockfd1);
    }
    bzero(&cliaddr1, sizeof(cliaddr1)); 
  
    // assign IP, PORT 
    cliaddr1.sin_family = AF_INET; 
    cliaddr1.sin_addr.s_addr = inet_addr("127.0.0.1"); 
    cliaddr1.sin_port = htons(PORT); 
  
    // connect the client socket to server socket 
    if (connect(sockfd1, (SA*)&cliaddr1, sizeof(cliaddr1)) != 0) { 
        printf("connection with the server failed...\n"); 
        exit(0); 
    } 
    else
        printf("connected to the server..\n"); 
  
    // function for chat 
    func(sockfd1); 
  
    // close the socket 
    close(sockfd1); 

} 
