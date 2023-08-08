#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 8000
#define MSG_SIZE 1024
#define LISTEN_BACKLOG 50

void error(char msg[])
{
    printf("\n%s\n\n", msg);
    exit(EXIT_FAILURE);
}

void main()
{
    int c_fd;
    struct sockaddr_in s_addr;
    socklen_t s_addr_len = sizeof(s_addr);

    // Socket Creation
    c_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (c_fd == -1)
       error("Socket creation failed!");
    else
        printf("\nSocket created successfully!");
       
    // Initializing Server Address Memory
    memset(&s_addr, 0, s_addr_len);
    
    // Filling Server Information
    s_addr.sin_family = AF_INET;
    s_addr.sin_port = htons(PORT);
    s_addr.sin_addr.s_addr = INADDR_ANY;

    // Connecting
    if (connect(c_fd, (struct sockaddr *) &s_addr, s_addr_len) == -1)
        error("Connection failed!");
    else
        printf("\nConnection established successfully!\n");
        
    char msg[MSG_SIZE], rev_msg[MSG_SIZE];
        
    while(1)
    {
        // Initializing Buffer
        memset(msg, 0, MSG_SIZE);
        memset(rev_msg, 0, MSG_SIZE);
        
        // Accepting Message
        printf("\nEnter the message: ");
        scanf("%[^\n]%*c", msg);
        
        // Sending Message
        if(send(c_fd, msg, MSG_SIZE, 0) == -1)
            error("Sending failed!");
            
        // Exit Check
        if(strcmp(msg, "Exit") == 0 || strcmp(msg, "exit") == 0)
            error("Exit");
            
        // Receiving Message
        if(recv(c_fd, rev_msg, MSG_SIZE, 0) == -1)
            error("Receiving failed!");
            
        // Printing Received Message
        printf("Received message: %s\n", rev_msg);
    }
        
    printf("\n\n");
    close(c_fd);
}
