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
    int s_fd, c_fd;
    struct sockaddr_in s_addr, c_addr;
    socklen_t s_addr_len = sizeof(s_addr), c_addr_len = sizeof(c_addr);

    // Initializing Server Address Buffer
    memset(&s_addr, 0, s_addr_len);

    // Socket Creation
    s_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (s_fd == -1)
       error("Socket creation failed!");
    else
        printf("\nSocket created successfully!");
    
    // Filling Server Information
    s_addr.sin_family = AF_INET;
    s_addr.sin_port = htons(PORT);
    s_addr.sin_addr.s_addr = INADDR_ANY;

    // Binding
    if (bind(s_fd, (struct sockaddr *) &s_addr, s_addr_len) == -1)
       error("Binding failed!");
    else
        printf("\nBinding completed successfully!");

    // Listening
    printf("\nListening..");
    if (listen(s_fd, LISTEN_BACKLOG) == -1)
       error("Listening failed! No clients found.");
    else
        printf("\nClient found.");
    
    // Accepting
    c_fd = accept(s_fd, (struct sockaddr *) &c_addr, &c_addr_len);      
    if (c_fd == -1)
       error("Accepting failed!");
    else
        printf("\nAccepted connection successfully!\n\n");
        
    char msg[MSG_SIZE], rev_msg[MSG_SIZE];
        
    while(1)
    {
        // Initializing Buffer
        memset(msg, 0, MSG_SIZE);
        memset(rev_msg, 0, MSG_SIZE);
        
        // Receiving Message
        if(recv(c_fd, msg, MSG_SIZE, 0) == -1)
            error("Receiving failed!");
        
        // Exit Check
        if(strcmp(msg, "Exit") == 0 || strcmp(msg, "exit") == 0)
            error("Exit");
            
        // Printing Received Message
        printf("Received message: %s\n", msg);
        
        // Reversing Message
        int i, msg_len = strlen(msg);
        
        for(i = 0; i < msg_len; i++)
            rev_msg[i] = msg[msg_len-i-1];
        
        // Sending Reversed Message
        if(send(c_fd, rev_msg, MSG_SIZE, 0) == -1)
            error("Sending failed!");
    }
       
    printf("\n\n");
    close(c_fd);
    close(s_fd);
}
